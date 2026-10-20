// Paired header
#include "packetPrinter/ethernetPrinter.hpp"
// My other headers
#include "packetFormat/ethernetFormat.hpp"  // For FormattedEthernet struct
#include "packetPrinter/printConfig.hpp"    // For print_space
// Standard library headers
#include <cstdio>   // For printf
#include <cstring>  // For c_str (for passing strings to printf)
#include <string>


void print_ethernet(const FormattedEthernet& ethernet) {
    std::string destination { "Destination: " + ethernet.dest };
    std::string source { "Source: " + ethernet.src };
    std::string ether_type {"EtherType: " + ethernet.ether_type };
    std::string protocol { "Protocol: " + ethernet.protocol };
    // Field specifiers %-ns:
    //  % -> start of specifier
    //  - -> left-aligned
    //  n -> width e.g. 30 chars wide; * takes this an an arg
    //  s -> type (string)
    printf("%-*s %-*s %-*s %-*s\n",
        static_cast<int>(destination.size() + PrintConfig::print_space), destination.c_str(),
        static_cast<int>(source.size() + PrintConfig::print_space), source.c_str(),
        static_cast<int>(ether_type.size() + PrintConfig::print_space), ether_type.c_str(),
        static_cast<int>(protocol.size() + PrintConfig::print_space), protocol.c_str()
    );
}