// Paired header
#include "packetPrinter/packetPrinter.hpp"
// My other headers
#include "packetFormat/packetFormat.hpp"    // For FormattedPacket struct
#include "packetPrinter/ethernetPrinter.hpp"

void print_packet(const FormattedPacket& formatted) {
    // Print time

    // Print ethernet
    print_ethernet(formatted.ethernet);

    // Print IP layer

    // Print TCP/UDP


}