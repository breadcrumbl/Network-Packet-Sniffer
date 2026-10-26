#pragma once
// My other headers
#include "packetParser/ethernetParser.hpp"  // For ParsedEthernet struct
//Standard library headers
#include <cstdint>  // For uintX_t
#include <string>
#include <vector>

struct FormattedEthernet {
    std::string dest {};
    std::string src {};
    std::string ether_type {};
    std::string protocol {};
};

FormattedEthernet format_ethernet(const ParsedEthernet& ethernet);
std::string mac_to_string(const std::vector<uint8_t>& mac_addr);
std::string ether_type_to_string(const uint16_t ether_type);
std::string ethernet_protocol_string(const uint16_t ether_type);