#pragma once

// My other headers
#include "packetCapture/packetCapture.hpp"  // For CapturedPacket struct
#include "packetParser/ethernetParser.hpp"  // For ParsedEthernet struct
#include "packetParser/ipParser.hpp"        // For ParsedIP struct
#include "packetParser/udpParser.hpp"        // For ParsedUDP struct
// Standard library headers
#include <chrono>   // For timestamp

struct ParsedPacket {
    std::chrono::system_clock::time_point time {};
    ParsedEthernet ethernet {};
    ParsedIPv4 ipv4 {};
    ParsedUDP udp {};
};

// Function declarations
ParsedPacket parse_packet(const CapturedPacket& packet);
