// Paired header
#include "packetFormat/udpFormat.hpp"
// My other headers
#include "packetParser/udpParser.hpp"       // For ParsedUDP struct
//Standard library headers
#include <string> 

FormattedUDP format_udp(const ParsedUDP& parsed) {
    FormattedUDP formatted {};
    formatted.src_port = std::to_string(parsed.src_port);
    formatted.dest_port = std::to_string(parsed.dest_port);
    formatted.length_bytes = std::to_string(parsed.length_bytes);
    formatted.checksum = std::to_string(parsed.checksum);
    return formatted;
}