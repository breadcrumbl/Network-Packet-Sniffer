// Paired headers
#include "packetParser/ipParser.hpp"
// My other headers
#include "packetParser/parsingConstants.hpp"
#include "packetParser/parsingFunctions.hpp"
// 3rd party headers
// Standard library headers
#include <cstddef>  // For std::size_t
#include <cstdint>  // For uint types
#include <cstdio>   // For std::printf
#include <optional> // For non-valid function returns
#include <vector>   // For storing data bytes

std::optional<ParsedIPv4> parse_ipv4(const std::vector<std::uint8_t>& data, const int offset) {
    // Check size
    std::size_t available_data { data.size() - ParsingConstants::ethernet_min_size };
    if (ParsingConstants::ipv4_min_size > available_data) {
        printf("Packet too short for IPv4 header\n");
        return std::nullopt;
    }

    // Track which byte is being parsed
    const std::uint8_t* data_ptr { data.data() +  offset };

    ParsedIPv4 parsed {};

    // Version (upper 4 bits of first byte; should be 4 for IPv4)
    // Shift first byte to the right 4 then apply mask that keeps only those 4 bits
    parsed.version = get_upper_x_bits(data_ptr, 4);
    // Defensive check as this is already checked in pased_packet() before calling parse_ipv4()
    if (parsed.version != 4) {
        printf("Version is not IPv4\n");
        return std::nullopt;
    }

    // Header length (lower 4 bits of first byte; should be at least 20 bytes)
    // IHL stored as a 4-bit number; convert to header length in bytes by x4 (e.g. IHL = 5 -> header length = 20 bytes)
    parsed.header_length_bytes = get_lower_x_bits(data_ptr, 4) * 4;
    // Check long enough for an IPv4 header
    if (parsed.header_length_bytes < ParsingConstants::ipv4_min_size) {
        printf("IHL too short for IPv4 header\n");
        return std::nullopt;
    }
    // Check data packet contains enough data for the stated header length
    if (parsed.header_length_bytes > available_data) {
        printf("Captured packet too short for declared IPv4 header\n");
        return std::nullopt;
    }
    // Shift byte to start of next bit of information
    ++data_ptr;

    // DSCP and ECN (upper 6 and lower 2 bits of next byte respectively)
    parsed.dscp = get_upper_x_bits(data_ptr, 6);
    parsed.ecn = get_lower_x_bits(data_ptr, 2);
    ++data_ptr;

    // Total length (next 16 bits, stored in Big-Endian)
    parsed.total_length_bytes = read_uint16(data_ptr);
    // Check total length is large enough to contain IPv4 header
    if (parsed.total_length_bytes < parsed.header_length_bytes) {
        printf("IPv4 total length is smaller than its header length\n");
        return std::nullopt;
    }
    

    // Identification (next 16 bits, Big-Endian)
    parsed.id = read_uint16(data_ptr);

    // Flags and fragment offset (next 16 bits, Big-Endian)
    parsed.reserved_flag = get_xth_bit(data_ptr, 1);
    if (parsed.reserved_flag != 0) {
        printf("Reserved flag should be 0 for IPv4\n");
        return std::nullopt;
    }
    parsed.df_flag = get_xth_bit(data_ptr, 2);
    parsed.mf_flag = get_xth_bit(data_ptr, 3);
    parsed.fragment_offset_bytes = static_cast<std::uint16_t>(8 * ( (get_lower_x_bits(data_ptr, 5) << 8) | *(data_ptr + 1) ) );
    data_ptr +=2;

    // TTL (1 byte)
    parsed.ttl = *data_ptr;
    ++data_ptr;

    // Protocol (1 byte)
    parsed.protocol = *data_ptr;
    ++data_ptr;

    // Header check sum (16 bits, Big-Endian)
    parsed.header_checksum = read_uint16(data_ptr);

    // Source IP address (32 bits arranged in 4 bytes)
    parsed.src_ip = read_address(data_ptr, parsed.src_ip.size());

    // Destination IP address (32 bits arranged in 4 bytes)
    parsed.dest_ip = read_address(data_ptr, parsed.dest_ip.size());

    // TO-DO: parse options if neccessary

    // TO-DO: update offset if greater than 20 bytes

    return parsed;
}


