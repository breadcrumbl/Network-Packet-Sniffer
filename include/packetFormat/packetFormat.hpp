#pragma once

#include "packetParser/packetParser.hpp"  // For ParsedPacket struct
#include "packetFormat/ethernetFormat.hpp"

struct FormattedPacket {
    FormattedEthernet ethernet {};
};

FormattedPacket format_packet(const ParsedPacket& captured);