#pragma once
// 3rd party library headers
#include <pcap.h>
// Standard library headers
#include <chrono>   // For timestamp
#include <cstdint>  // For uint types for CapturedPacket struct
#include <optional> // For std::optional
#include <vector>   // For data

struct CapturedPacket {
    std::chrono::system_clock::time_point time {};
    std::uint32_t captured_length {};
    std::uint32_t original_length {};
    std::vector<std::uint8_t> data {};
};

// Function declarations
std::optional<CapturedPacket> capture_packet(pcap_t* handle);
