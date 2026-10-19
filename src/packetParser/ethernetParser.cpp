// Paired headers
#include "packetParser/ethernetParser.hpp"
// My other headers
#include "packetCapture/packetCapture.hpp"    // For Packet struct
// Standard library headers
#include <cstdint>  // For uint16_t for Ether Type
#include <optional> // For non-valid function returns
#include <vector>   // For storing MAC address bytes


// Reads the first 14 bytes of header to a EthernetHeader struct, return this if successful, std::nullopt if not
std::optional<EthernetHeader> parse_ethernet(const CapturedPacket& packet) {
    // Check size
    if (packet.data.size() < EthernetHeader::ethernet_header_min_size) {
        printf("Packet too short for Ethernet header\n");
        return std::nullopt;
    }
    // Ethernet header to be returned
    EthernetHeader ethernet {};
    // Pointer to first byte of data
    // Note: const <type>* <name> -> data cannot be modified but ptr can; <type>* const <name> -> ptr cannot be modifed but data can
    const u_char* data_ptr { packet.data.data() };

    // Parse destintion MAC
    for (int i { 0 }; i < static_cast<int>(ethernet.dest_mac.size()); ++i) {
        ethernet.dest_mac[i] = *data_ptr++;
    }
    // Parse source MAC
    for (int i { 0 }; i < static_cast<int>(ethernet.src_mac.size()); ++i) {
        ethernet.src_mac[i] = *data_ptr++;
    }
    // Parse Ether type (Network Protocols parse this big-endian)
    ethernet.ether_type = static_cast<std::uint16_t>(*data_ptr << 8) | static_cast<std::uint16_t>(*(data_ptr + 1));
    return ethernet;    
}
