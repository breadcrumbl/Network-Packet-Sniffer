#pragma once

// My other headers
#include "packetCapture/packetCapture.hpp"  // For CapturedPacket struct
#include "packetParser/ethernetParser.hpp"  // For ParsedEthernet struct
// Standard library headers
#include <chrono>   // For timestamp

struct ParsedPacket {
    std::chrono::system_clock::time_point time {};
    ParsedEthernet ethernet {};
};

// Function declarations
ParsedPacket parse_packet(const CapturedPacket& packet);
