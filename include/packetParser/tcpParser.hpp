#pragma once

#include <cstdint>
#include <optional>
#include <vector>

struct ParsedTCP {
    std::uint16_t src_port {};                 // Source application port (16 bits).
    std::uint16_t dest_port {};                // Destination application port (16 bits).
    std::uint32_t sequence_number {};          // Position of data in the TCP byte stream (32 bits).
    std::uint32_t acknowledgement_number {};  // Next byte expected from the sender (32 bits).
    std::uint8_t data_offset_bytes {};         // TCP header length in bytes (4 bits in packet).
    std::uint8_t reserved {};                  // Reserved for future use (4 bits).
    std::uint8_t flags {};                     // TCP control flags: CWR, ECE, URG, ACK, PSH, RST, SYN, FIN (8 bits).
    std::uint16_t window_size {};              // Advertised receive window (16 bits).
    std::uint16_t checksum {};                 // TCP header and data integrity checksum (16 bits).
    std::uint16_t urgent_pointer {};           // Position of urgent data when URG is set (16 bits).
};

std::optional<ParsedTCP> parse_tcp(const std::vector<std::uint8_t>& data, const int offset);
