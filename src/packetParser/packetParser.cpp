// Paired headers
#include "packetParser/packetParser.hpp"
// My other headers
#include "packetParser/ethernetParser.hpp"
#include "packetParser/ipParser.hpp"      
#include "packetParser/tcpParser.hpp"  
#include "packetParser/udpParser.hpp"
//#include "packetPrinter/ethernetPrinter.hpp"
#include "packetCapture/packetCapture.hpp"
// 3rd party headers
#include <pcap.h>
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <optional> // For non-valid function returns
#include <vector>   // For storing data bytes


ParsedPacket parse_packet(const CapturedPacket& raw) {
    ParsedPacket parsed {};
    // Parse time 
    parsed.time = raw.time;

    // Parse Ethernet header
    auto ethernet { parse_ethernet(raw) };
    if (!ethernet) {
        return parsed;
    }
    // * accesses EthernetHeader in std::optional<ParsedEthernet>
    parsed.ethernet = new ParsedEthernet(*ethernet);

    // Parse IP layer
    // Parse IPv4 layer
    // TO-DO: have this as enum
    if (parsed.ethernet->ether_type == 0x0800) {

        auto ipv4 { parse_ipv4(raw.data, parsed.ethernet->payload_offset) };
        if (!ipv4) {
            return parsed;
        }
        parsed.ipv4 = new ParsedIPv4(*ipv4);

        printf("IPv4 packet detected\n");
        printf("IPv4 protocol number: %u\n", static_cast<unsigned>(parsed.ipv4->protocol));

        // Parse TCP/UDP layer
        // TO-DO: have this as enum, don't hardcode
        if (parsed.ipv4->protocol == 17) {
            auto udp { parse_udp(raw.data, parsed.ipv4->payload_offset) };
            if (!udp) {
                return parsed;
            }
            parsed.udp = new ParsedUDP(*udp);
        } 
        else if (parsed.ipv4->protocol == 6) {
            printf("Parsing TCP\n");
            auto tcp { parse_tcp(raw.data, parsed.ipv4->payload_offset) };
            if (!tcp) {
                return parsed;
            }
            parsed.tcp = new ParsedTCP(*tcp);
        } 
    }


    // Parse payload

    return parsed;
}


void cleanup_parsed_packet(ParsedPacket& parsed) {
    delete parsed.ethernet;
    delete parsed.ipv4;
    delete parsed.udp;
    delete parsed.tcp;

    parsed.ethernet = nullptr;
    parsed.ipv4 = nullptr;
    parsed.udp = nullptr;
    parsed.tcp = nullptr;
}







