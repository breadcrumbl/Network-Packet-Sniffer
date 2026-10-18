#pragma once

// My other headers
#include "packetParser/ethernetParser.hpp"   // For EthernetHeader struct
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <string>
#include <vector>

// Function declarations
void print_ethernet(const EthernetHeader& header);
std::string mac_to_string(const std::vector<u_char>& mac_addr);
std::string ether_type_to_string(const uint16_t ether_type);
std::string protocol_string(const uint16_t ether_type);