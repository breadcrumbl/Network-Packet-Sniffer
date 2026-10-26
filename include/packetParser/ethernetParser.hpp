#pragma once

// My other headers
#include "packetCapture/packetCapture.hpp"    // For CapturedPacket struct
#include "packetParser/parsingConstants.hpp"
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <optional> // For non-valid function returns
#include <vector>   // For storing MAC address bytes

struct ParsedEthernet { 
    // Static member variables (shared by all members of the class rather than each member getting its own copy)
    static constexpr int mac_size { 6 };
    static constexpr int ether_type_size { 2 };

    // Member variables
    // Destination MAC: bytes 0-5
    // Source MAC:      bytes 6-11
    // EtherType:       bytes 12-13
    // Note direct initialisation (e.g. destMAC(6)) is not allowed for member defualt initiliasers
    // Must use list initiliasion: create the std::vector with desired length and use this as initaliser
    std::vector<std::uint8_t> dest_mac { std::vector<std::uint8_t>( mac_size ) };
    std::vector<std::uint8_t> src_mac { std::vector<std::uint8_t>( mac_size ) };
    std::uint16_t ether_type {};
    // TO-DO: add an offset calculator to work this out 
    int payload_offset { ParsingConstants::ethernet_min_size };          // In case Ethernet header is more than 14 bytes (has VLAN flags); passed to parse IP functions to tell them where to start
};

// TO:DO have ether type as an enum

// Function declarations
std::optional<ParsedEthernet> parse_ethernet(const CapturedPacket& packet);