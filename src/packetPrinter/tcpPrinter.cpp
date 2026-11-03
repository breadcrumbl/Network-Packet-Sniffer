#include "packetPrinter/tcpPrinter.hpp"

#include <iostream>

void print_tcp(const FormattedTCP& formatted) {
    std::cout << "\nTCP HEADER\n";
    std::cout << "Source Port: " << formatted.src_port << '\n';
    std::cout << "Destination Port: " << formatted.dest_port << '\n';
    std::cout << "Sequence Number: " << formatted.sequence_number << '\n';
    std::cout << "Acknowledgement Number: " << formatted.acknowledgement_number << '\n';
    std::cout << "Header Length: " << formatted.data_offset_bytes << " bytes\n";
    std::cout << "Reserved: " << formatted.reserved << '\n';
    std::cout << "Flags: " << formatted.flags << '\n';
    std::cout << "Window Size: " << formatted.window_size << '\n';
    std::cout << "Checksum: " << formatted.checksum << '\n';
    std::cout << "Urgent Pointer: " << formatted.urgent_pointer << '\n';
}