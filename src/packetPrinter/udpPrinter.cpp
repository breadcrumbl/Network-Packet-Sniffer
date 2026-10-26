// Paired header
#include "packetPrinter/udpPrinter.hpp"
// My other headers
#include "packetFormat/udpFormat.hpp"   // For FormattedUDP struct
// Standard library headers
#include <iostream>

void print_udp(const FormattedUDP& formatted) {
    std::cout << "UDP Header\n"
              << "  Source port:      " << formatted.src_port << '\n'
              << "  Destination port: " << formatted.dest_port << '\n'
              << "  Length:           " << formatted.length_bytes << " bytes\n"
              << "  Checksum:         " << formatted.checksum << '\n';
}