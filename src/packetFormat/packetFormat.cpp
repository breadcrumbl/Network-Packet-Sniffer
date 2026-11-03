// Paired header
#include "packetFormat/packetFormat.hpp"
// My other headers
#include "packetFormat/ethernetFormat.hpp"
#include "packetFormat/ipFormat.hpp"
#include "packetFormat/tcpFormat.hpp"
#include "packetFormat/udpFormat.hpp"
#include "packetFormat/timeFormat.hpp"
#include "packetParser/packetParser.hpp"  // For ParsedPacket struct

FormattedPacket format_packet(const ParsedPacket& parsed) {
    FormattedPacket formatted {};
    // Format time
    formatted.time = format_time(parsed.time);

    // Format ethernet header
    if (parsed.ethernet != nullptr) {
        formatted.ethernet = new FormattedEthernet(format_ethernet(*parsed.ethernet));
    }

    // Format IP layer
    if (parsed.ipv4 != nullptr) {
        formatted.ipv4 = new FormattedIPv4(format_ipv4(*parsed.ipv4));
    }

    // Format TCP/UDP layer
    if (parsed.udp != nullptr) {
        formatted.udp = new FormattedUDP(format_udp(*parsed.udp));
    }
    if (parsed.tcp != nullptr) {
        formatted.tcp = new FormattedTCP(format_tcp(*parsed.tcp));
    }

    // Format data layer
    
    return formatted;
}


void cleanup_formatted_packet(FormattedPacket& formatted) {
    delete formatted.ethernet;
    delete formatted.ipv4;
    delete formatted.udp;
    delete formatted.tcp;

    formatted.ethernet = nullptr;
    formatted.ipv4 = nullptr;
    formatted.udp = nullptr;
    formatted.tcp = nullptr;
}