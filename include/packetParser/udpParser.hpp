#pragma once

#include "packetParser/parsingConstants.hpp"    // For ipv4_min_size

#include <cstdint>
#include <optional>
#include <vector>

struct ParsedUDP {
    std::uint16_t src_port {};      // 16 bits: Source application port; 0 if no source port used
    std::uint16_t dest_port {};     // 16 bits: Destination application port
    std::uint16_t length_bytes {};  // 16 bits: Total UDP header + data length, in bytes
    std::uint16_t checksum {};      // 16 bits: Error-detection checksum for UDP header and data; 0 means sender did not provide a checksum

    int payload_offset { ParsingConstants::ipv4_min_size };
};

// Function declarations
std::optional<ParsedUDP> parse_udp(const std::vector<std::uint8_t>& data, const int offset);