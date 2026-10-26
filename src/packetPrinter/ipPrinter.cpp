
// Paired header
#include "packetPrinter/ipPrinter.hpp"
#include "packetPrinter/printConfig.hpp"    // For print_space
// My other headers

// Standard library headers
#include <iostream>
#include <iomanip>
#include <string>

void print_ipv4(const FormattedIPv4& ipv4) {
    constexpr int label_width = 24;
    constexpr int value_width = 16;
    constexpr int gap = PrintConfig::print_space;

    std::cout << std::left
              << std::setw(label_width) << "Version:" 
              << std::setw(value_width) << ipv4.version
              << std::string(gap, ' ')
              << std::setw(label_width) << "Header length:"
              << std::setw(value_width) << ipv4.header_length_bytes
              << std::string(gap, ' ')
              << std::setw(label_width) << "DSCP:"
              << std::setw(value_width) << ipv4.dscp
              << std::string(gap, ' ')
              << std::setw(label_width) << "ECN:"
              << ipv4.ecn << '\n';

    std::cout << std::left
              << std::setw(label_width) << "Total length:"
              << std::setw(value_width) << ipv4.total_length_bytes
              << std::string(gap, ' ')
              << std::setw(label_width) << "Identification:"
              << std::setw(value_width) << ipv4.id
              << std::string(gap, ' ')
              << std::setw(label_width) << "Reserved flag:"
              << std::setw(value_width) << ipv4.reserved_flag
              << std::string(gap, ' ')
              << std::setw(label_width) << "DF flag:"
              << ipv4.df_flag << '\n';

    std::cout << std::left
              << std::setw(label_width) << "MF flag:"
              << std::setw(value_width) << ipv4.mf_flag
              << std::string(gap, ' ')
              << std::setw(label_width) << "Fragment offset:"
              << std::setw(value_width) << ipv4.fragment_offset_bytes
              << std::string(gap, ' ')
              << std::setw(label_width) << "TTL:"
              << std::setw(value_width) << ipv4.ttl
              << std::string(gap, ' ')
              << std::setw(label_width) << "Protocol:"
              << ipv4.protocol << '\n';

    std::cout << std::left
              << std::setw(label_width) << "Header checksum:"
              << std::setw(value_width) << ipv4.header_checksum
              << std::string(gap, ' ')
              << std::setw(label_width) << "Source IP:"
              << std::setw(value_width) << ipv4.src_ip
              << std::string(gap, ' ')
              << std::setw(label_width) << "Destination IP:"
              << ipv4.dest_ip << '\n';
}
