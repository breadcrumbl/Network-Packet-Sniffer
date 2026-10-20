#pragma once

#include "packetParser/packetParser.hpp"  // For ParsedPacket struct
#include "packetFormat/ethernetFormat.hpp"

#include <string>

struct FormattedPacket {
    std::string time {};
    FormattedEthernet ethernet {};
};

FormattedPacket format_packet(const ParsedPacket& captured);