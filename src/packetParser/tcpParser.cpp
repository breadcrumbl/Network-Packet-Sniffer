#include "packetParser/tcpParser.hpp"

#include "packetParser/parsingFunctions.hpp"
#include "packetParser/parsingConstants.hpp"

#include <cstddef>  //tsd::size_t
#include <cstdint> 
#include <iostream>  // std::cerr

// Parse TCP header
std::optional<ParsedTCP> parse_tcp(const std::vector<std::uint8_t>& data, const int offset) {
    // Check that the offset is not negative.
    if (offset < 0) {
        std::cerr << "TCP parsing error: offset is negative.\n";
        return std::nullopt;
    }

    // Convert offset to size_t after confirming it is non-negative.
    const std::size_t data_offset { static_cast<std::size_t>(offset) };

    // Check that the offset does not exceed the available data.
    if (data_offset > data.size()) {
        std::cerr << "TCP parsing error: offset exceeds packet size.\n";
        return std::nullopt;
    }

    // Check that at least 20 bytes remain for the minimum TCP header.
    if (data.size() - data_offset < 20) {
        std::cerr << "TCP parsing error: insufficient data for minimum TCP header.\n";
        return std::nullopt;
    }

    const std::uint8_t* data_ptr { data.data() + offset };

    ParsedTCP parsed {};

    // Source and destination ports (16 bits each)
    parsed.src_port = read_uint16(data_ptr);
    parsed.dest_port = read_uint16(data_ptr);

    // Sequence and acknowledgement numbers (32 bits each)
    parsed.sequence_number = read_uint32(data_ptr);
    parsed.acknowledgement_number = read_uint32(data_ptr);

    // Data offset (bytes) and reserved bits
    parsed.data_offset_bytes = static_cast<std::uint8_t>(get_upper_x_bits(data_ptr, 4) * 4);
    parsed.reserved = get_lower_x_bits(data_ptr, 4);
    ++data_ptr;

    // TCP flags
    parsed.flags = *data_ptr++;

    // Window size, checksum and urgent pointer
    parsed.window_size = read_uint16(data_ptr);
    parsed.checksum = read_uint16(data_ptr);
    parsed.urgent_pointer = read_uint16(data_ptr);

    // Validate TCP header length
    if (parsed.data_offset_bytes < 20 ||
        parsed.data_offset_bytes > data.size() - static_cast<std::size_t>(offset)) {
        return std::nullopt;
    }

    return parsed;
}