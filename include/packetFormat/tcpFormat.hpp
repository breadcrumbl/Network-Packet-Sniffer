#pragma once

#include "packetParser/tcpParser.hpp"

#include <cstdint>
#include <string>

struct FormattedTCP {
    std::string src_port {};
    std::string dest_port {};
    std::string sequence_number {};
    std::string acknowledgement_number {};
    std::string data_offset_bytes {};
    std::string reserved {};
    std::string flags {};
    std::string window_size {};
    std::string checksum {};
    std::string urgent_pointer {};
};

FormattedTCP format_tcp(const ParsedTCP& parsed);
std::string format_tcp_flags(const std::uint8_t flags);