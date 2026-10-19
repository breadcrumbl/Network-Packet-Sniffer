#pragma once

// My other headers
#include "packetCapture/packetCapture.hpp"  // For Packet struct
#include "packetParser/ethernetParser.hpp"  // For EthernetHeader struct

struct ParsedPacket {
    EthernetHeader ethernet {};
};

// Function declarations
ParsedPacket parse_packet(const CapturedPacket& packet);
