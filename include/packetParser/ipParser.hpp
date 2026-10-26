#pragma once

#include "packetParser/parsingConstants.hpp"

#include <cstdint> 
#include <optional> // For non-valid function returns
#include <vector>

/*
* IPv4 layer:
* Version (4 bits): Always set to 0100 (4 in binary) for IPv4.
* IHL (4 bits): Internet Header Length, telling the system how long the header is.
* Type of Service (8 bits): Used for packet prioritization. Split into DSCP and ECN: 
*   DSCP: Differentiated Services Code Point (6 bits) indicate the desired treatment of a packet by network equipment
*   ECN: Explicit Congestion Notification, communicates congestion information
* Total Length (16 bits): The size of the entire packet (header + data).
* Identification, Flags, Fragment Offset (32 bits total): Used if the packet needs to be split up (fragmented).
*   ID: 16 bits
*   Reserved: 1 bit, should be 0 for IPv4
*   DF: Don't Fragment (1 bit), 0 if fragmentation is allowed, 1 if not
*   MR: More Fragment (1 bit), 0 if this is the final fragment or the packet was never fragmented, 1 if more fragments follow this one
*   Fragment offset: 13 bit offset measured in units of 8 bytes (e.g. offset=185 means start at byte 185*8 in payload); max is 8*13=8191 so uint16_t should be fine
* Time to Live (TTL) (8 bits): A counter that prevents packets from looping forever. Each router that forwards the packet reduces this count by at least one and packet is dropped if this is 0.
* Protocol (8 bits): Tells the system what comes next (e.g., 6 for TCP, 17 for UDP).
* Header Checksum (16 bits): Used to check for errors in the header.
* Source IP Address (32 bits): The sender's 4-byte IP address.
* Destination IP Address (32 bits): The receiver's 4-byte IP address.
* Options (Variable): Optional extra settings (rarely used).
*/

#include <cstdint>

enum class IPProtocol : std::uint8_t {
    ICMP        = 1,
    IGMP        = 2,
    TCP         = 6,
    UDP         = 17,
    IPv6        = 41,
    GRE         = 47,
    ESP         = 50,
    AH          = 51,
    OSPF        = 89,
    SCTP        = 132
};

struct ParsedIPv4 {
    // Static member variables
    static constexpr int ip_addr_len { 4 };
    // Member variables
    std::uint8_t version {};                // Should be 4 for now (4 bits)
    std::uint8_t header_length_bytes {};    // In bytes (4 bits)
    std::uint8_t dscp {};                   // 6 bits
    std::uint8_t ecn {};                    // 2 bits
    std::uint16_t total_length_bytes {};    // Size of packet including header in bytes (16 bits)
    std::uint16_t id {};                    // Idenitifcation (16 bits)
    std::uint8_t reserved_flag {};          // 1 bit, 0 or 1
    std::uint8_t df_flag {};                // 1 bit, 0 or 1
    std::uint8_t mf_flag {};                // 1 bit, 0 or 1
    std::uint16_t fragment_offset_bytes {};       // 13 bits, in bytes
    std::uint8_t ttl {};                    // Max remaining router hops (8 bits)
    std::uint8_t protocol {};               // Next-layer protocol e.g. TCP/UDP
    std::uint16_t header_checksum {};       // 16 bits, use to validate the IP header 
    std::vector<std::uint8_t> src_ip { std::vector<std::uint8_t>( ip_addr_len ) };  // (32 bits arranged in 4 bytes)
    std::vector<std::uint8_t> dest_ip { std::vector<std::uint8_t>( ip_addr_len ) }; //(32 bits arranged in 4 bytes)
    // TO-DO int options {};            

    int payload_offset { ParsingConstants::ethernet_min_size + ParsingConstants::ipv4_min_size };                  // Used to tell next layer where to start parsing
};

// Function declarations
std::optional<ParsedIPv4> parse_ipv4(const std::vector<std::uint8_t>& data, const int offset);