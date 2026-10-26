#pragma once

#include "packetParser/udpParser.hpp"       // For ParsedUDP struct

#include <string>

struct FormattedUDP {
    std::string src_port {};      // 16 bits: Source application port; 0 if no source port used
    std::string dest_port {};     // 16 bits: Destination application port
    std::string length_bytes {};  // 16 bits: Total UDP header + data length, in bytes
    std::string checksum {};      // 16 bits: Error-detection checksum for UDP header and data; 0 means sender did not provide a checksum
};

// Function declarations
FormattedUDP format_udp(const ParsedUDP& parsed);