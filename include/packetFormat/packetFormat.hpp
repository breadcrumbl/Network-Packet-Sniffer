#pragma once

#include "packetParser/packetParser.hpp"  // For ParsedPacket struct
#include "packetFormat/ethernetFormat.hpp"
#include "packetFormat/ipFormat.hpp"
#include "packetFormat/udpFormat.hpp"

#include <string>

struct FormattedPacket {
    std::string time {};
    FormattedEthernet ethernet {};
    FormattedIPv4 ipv4 {};
    FormattedUDP udp {};
};

FormattedPacket format_packet(const ParsedPacket& captured);