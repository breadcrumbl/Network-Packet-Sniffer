// Paired headers
#include "packetParser/packetParser.hpp"
// My other headers
#include "packetParser/ethernetParser.hpp"
#include "packetParser/udpParser.hpp"
#include "packetParser/ipParser.hpp"      
#include "packetPrinter/ethernetPrinter.hpp"
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
    parsed.ethernet = *ethernet;

    // Parse IP layer
    // Parse IPv4 layer
    // TO-DO: have this as enum
    if (parsed.ethernet.ether_type == 0x0800) {
        auto ipv4 { parse_ipv4(raw.data, parsed.ethernet.payload_offset) };
        if (!ipv4) {
            return parsed;
        }
        parsed.ipv4 = *ipv4;

        // Parse TCP/UDP layer
        if (parsed.ipv4.protocol == 17) {
            auto udp { parse_udp(raw.data, parsed.ipv4.payload_offset) };
            if (!udp) {
                return parsed;
            }
            parsed.udp = *udp;
        } 
    }


    // Parse payload

    return parsed;
}








