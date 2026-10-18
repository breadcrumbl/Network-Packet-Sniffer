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


void parse_packet(const Packet& packet) {
    // Parse time 

    // Parse Ethernet header
    auto header { parse_ethernet(packet) };
    if (!header) {
        return;
    }
    // * accesses EthernetHeader in std::optional<EthernetHeader>
    print_ethernet(*header);

    // Parse IP layer

    // Parse TCP/UDP layer

    // Parse payload

}








