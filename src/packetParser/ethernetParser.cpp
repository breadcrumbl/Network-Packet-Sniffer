// Paired headers
#include "packetParser/ethernetParser.hpp"
// My other headers
#include "packetCapture/packetCapture.hpp"    // For Packet struct
#include "packetParser/parsingConstants.hpp"
#include "packetParser/parsingFunctions.hpp"
// Standard library headers
#include <cstddef>  // For std::size_t
#include <cstdint>  // For uint types
#include <cstdio>   // For printf
#include <optional> // For non-valid function returns
#include <vector>   // For storing MAC address bytes


// Reads the first 14 bytes of header to a EthernetHeader struct, return this if successful, std::nullopt if not
std::optional<ParsedEthernet> parse_ethernet(const CapturedPacket& packet) {
    // Check size
    if (packet.data.size() < ParsingConstants::ethernet_min_size) {
        printf("Packet too short for Ethernet header\n");
        return std::nullopt;
    }

    // Ethernet header to be returned
    ParsedEthernet ethernet {};
    // Pointer to first byte of data
    // Note: const <type>* <name> -> data cannot be modified but ptr can; <type>* const <name> -> ptr cannot be modifed but data can
    const std::uint8_t* data_ptr { packet.data.data() };

    // Parse destintion MAC
    ethernet.dest_mac = read_address(data_ptr, ethernet.dest_mac.size());

    // Parse source MAC
    ethernet.src_mac = read_address(data_ptr, ethernet.src_mac.size());

    // Parse Ether type (Network Protocols parse this big-endian)
    ethernet.ether_type = read_uint16(data_ptr);

    return ethernet;    
    
}
