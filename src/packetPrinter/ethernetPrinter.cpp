// Paired header
#include "packetPrinter/ethernetPrinter.hpp"
// My other headers
#include "packetParser/ethernetParser.hpp"   // For EthernetHeader struct
// 3rd party library headers
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <cstdio>   // For printf
#include <cstring>  // For c_str (for passing strings to printf)
#include <iomanip>  // For string manipulation
#include <string>


// MAC address format: XX:XX:XX:XX:XX:XX (hexadecimal)
// Ether type format: XxXXXX (hexadecimal) e.g. 0x0000
void print_ethernet(const EthernetHeader& header) {
    std::string destination { "Destination: " + mac_to_string(header.dest_mac) };
    std::string source { "Source: " + mac_to_string(header.src_mac) };
    std::string ether_type {"EtherType: " + ether_type_to_string(header.ether_type) };
    std::string protocol { "Protocol: " + protocol_string(header.ether_type) };
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

std::string mac_to_string(const std::vector<u_char>& mac_addr) {
    // Create a string stream
    std::ostringstream mac_str {};
    // Configure output: 
    //  std::hex -> integers in hex rather than dec
    //  std::uppercase -> uppercase 
    //  std::setfill(0'') -> padding should use char 0 (important when we format each byte to be exactly 2 chars)
    mac_str << std::hex << std::uppercase << std::setfill('0');
    // Iterate over bytes
    for (int i { 0 }; i < static_cast<int>(mac_addr.size()); ++i) {
        // Add colon between bytes
        if (i > 0) {
            mac_str << ":";
        }
        // Add byte
        //  std::setw(2) -> sets the min field width of 2 (e.g. 05 instead of 5, 0 padding specified earlier)
        mac_str << std::setw(2) << static_cast<unsigned int>(mac_addr[i]);
    }
    return mac_str.str();
}

std::string ether_type_to_string(const uint16_t ether_type) {
    std::ostringstream ether_type_str {};
    ether_type_str  << std::hex << std::uppercase << std::setfill('0')              // Configure 
                    << std::setw(4) << static_cast<unsigned int>(ether_type);       // Pass value     
    return ether_type_str.str();
}

std::string protocol_string(const uint16_t ether_type) {
    if (ether_type == 0x0800) {
        return "IPv4";
    }
    else if (ether_type == 0x86DD) {
        return "IPv6";
    }
    else if (ether_type == 0x0806) {
        return "ARP";
    }
    else {
        return "Unknown or other";
    }
}