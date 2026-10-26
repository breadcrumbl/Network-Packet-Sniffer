// Paired header
#include "packetFormat/packetFormat.hpp"
// My other headers
#include "packetFormat/ethernetFormat.hpp"
#include "packetFormat/ipFormat.hpp"
#include "packetFormat/timeFormat.hpp"
#include "packetParser/packetParser.hpp"  // For ParsedPacket struct

FormattedPacket format_packet(const ParsedPacket& parsed) {
    FormattedPacket formatted {};
    // Format time
    formatted.time = format_time(parsed.time);

    // Format ethernet header
    formatted.ethernet = format_ethernet(parsed.ethernet);

    // Format IP layer
    formatted.ipv4 = format_ipv4(parsed.ipv4);

    // Format TCP/UDP layer
    formatted.udp = format_udp(parsed.udp);

    // Format data layer
    
    return formatted;
}