// Paired headers
#include "packetParser/packetParser.hpp"
// My other headers
#include "packetParser/ethernetParser.hpp"
#include "packetPrinter/ethernetPrinter.hpp"
#include "packetCapture/packetCapture.hpp"
// 3rd party headers
#include <pcap.h>
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <cstdio>   // For printf
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

    // Parse TCP/UDP layer

    // Parse payload

    return parsed;
}








