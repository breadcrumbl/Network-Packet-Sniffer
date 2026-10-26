// Paired header
#include "packetParser/udpParser.hpp"
// My other headers
#include "packetParser/parsingFunctions.hpp"
// Standard library headers
#include <cstdint>
#include <optional>
#include <vector>

std::optional<ParsedUDP> parse_udp(const std::vector<std::uint8_t>& data, const int offset) {
    const std::uint8_t* data_ptr { data.data() +  offset };
    ParsedUDP parsed {};
    parsed.src_port = read_uint16(data_ptr);
    parsed.dest_port = read_uint16(data_ptr);
    parsed.length_bytes = read_uint16(data_ptr);
    parsed.checksum = read_uint16(data_ptr);
    return parsed;
}