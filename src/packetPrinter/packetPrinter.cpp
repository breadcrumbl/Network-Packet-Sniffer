// Paired header
#include "packetPrinter/packetPrinter.hpp"
// My other headers
#include "packetFormat/packetFormat.hpp"    // For FormattedPacket struct
#include "packetPrinter/ethernetPrinter.hpp"
#include "packetPrinter/ipPrinter.hpp"
#include "packetPrinter/udpPrinter.hpp"
#include "packetPrinter/timePrinter.hpp"
// Standard library headers


void print_packet(const FormattedPacket& formatted) {
    // Print time
    print_time(formatted.time);

    // Print ethernet
    print_ethernet(formatted.ethernet);

    // Print IP layer
    print_ipv4(formatted.ipv4);

    // Print TCP/UDP
    print_udp(formatted.udp);


}