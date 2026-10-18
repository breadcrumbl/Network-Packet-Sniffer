#pragma once

// My other headers
#include "packetCapture/packetCapture.hpp"    // For Packet struct
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <optional> // For non-valid function returns
#include <vector>   // For storing MAC address bytes

struct EthernetHeader { 
    // Static member variables (shared by all members of the class rather than each member getting its own copy)
    // Ethernet II headers need at least 14 bytes
    static constexpr int ethernet_header_min_size { 14 };
    static constexpr int mac_size { 6 };
    static constexpr int ether_type_size { 2 };

    // Member variables
    // Destination MAC: bytes 0-5
    // Source MAC:      bytes 6-11
    // EtherType:       bytes 12-13
    // Note direct initialisation (e.g. destMAC(6)) is not allowed for member defualt initiliasers
    // Must use list initiliasion: create the std::vector with desired length and use this as initaliser
    std::vector<u_char> dest_mac { std::vector<u_char>( mac_size ) };
    std::vector<u_char> src_mac { std::vector<u_char>( mac_size ) };
    std::uint16_t ether_type {};
};

// Function declarations
std::optional<EthernetHeader> parse_ethernet(const Packet& packet);