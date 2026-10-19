// Paired header
#include "packetPrinter/ethernetPrinter.hpp"
// My other headers
#include "packetFormat/ethernetFormat.hpp"   // For FormattedEthernet struct
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
        static_cast<int>(destination.size() + 4), destination.c_str(),
        static_cast<int>(source.size() + 4), source.c_str(),
        static_cast<int>(ether_type.size() + 4), ether_type.c_str(),
        static_cast<int>(protocol.size() + 4), protocol.c_str()
    );
}