// Paired header
#include "packetFormat/packetFormat.hpp"
// My other headers
#include "packetFormat/ethernetFormat.hpp"
#include "packetFormat/timeFormat.hpp"
#include "packetParser/packetParser.hpp"  // For ParsedPacket struct

FormattedPacket format_packet(const ParsedPacket& parsed) {
    FormattedPacket formatted {};
    // Format time
    formatted.time = format_time(parsed.time);

    // Format ethernet header
    formatted.ethernet = format_ethernet(parsed.ethernet);

    // Format IP layer

    // Format TCP/UDP layer

    // Format data layer
    
    return formatted;
}