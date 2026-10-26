// Paired header
#include "packetFormat/ipFormat.hpp"
// My other headers
#include "packetParser/ipParser.hpp"
// Standard library headers
#include <sstream>  // For std::ostringstream (streams that read or write to strings)
#include <string>

FormattedIPv4 format_ipv4(const ParsedIPv4& parsed) {
    FormattedIPv4 formatted {};
    // Numbers
    formatted.version = std::to_string(parsed.version);
    formatted.header_length_bytes = std::to_string(parsed.header_length_bytes);
    formatted.dscp = std::to_string(parsed.dscp);
    formatted.ecn = std::to_string(parsed.ecn);
    formatted.total_length_bytes = std::to_string(parsed.total_length_bytes);
    formatted.id = std::to_string(parsed.id);
    formatted.reserved_flag = std::to_string(parsed.reserved_flag);
    
    if (parsed.df_flag == 0) {
        formatted.df_flag = "OFF";
    }
    else {
        formatted.df_flag = "ON";
    }
    if (parsed.mf_flag == 0) {
        formatted.mf_flag = "OFF";
    }
    else {
        formatted.mf_flag = "ON";
    }

    formatted.fragment_offset_bytes = std::to_string(parsed.fragment_offset_bytes);
    formatted.ttl = std::to_string(parsed.ttl);

    formatted.protocol = ip_protocol_string(parsed.protocol);

    // TO-DO: Deal with checksum 

    formatted.src_ip = ipv4_to_string(parsed.src_ip);
    formatted.dest_ip = ipv4_to_string(parsed.dest_ip);
    
    // TO-DO: deal with options
  
    return formatted;
}

std::string ip_protocol_string(std::uint8_t protocol) {
    switch (static_cast<IPProtocol>(protocol)) {
        case IPProtocol::ICMP:
            return "ICMP";
        case IPProtocol::IGMP:
            return "IGMP";
        case IPProtocol::TCP:
            return "TCP";
        case IPProtocol::UDP:
            return "UDP";
        case IPProtocol::IPv6:
            return "IPv6 encapsulation";
        case IPProtocol::GRE:
            return "GRE";
        case IPProtocol::ESP:
            return "ESP (IPsec)";
        case IPProtocol::AH:
            return "AH (IPsec)";
        case IPProtocol::OSPF:
            return "OSPF";
        case IPProtocol::SCTP:
            return "SCTP";
        default:
            return "Unknown / unsupported";
    }
}

std::string ipv4_to_string(const std::vector<std::uint8_t>& ip) {
    std::ostringstream ip_str {};
    for (std::size_t i { 0 }; i < ip.size(); ++i) {
        if (i > 0) {
            ip_str << ".";
        }
        ip_str << static_cast<unsigned int>(ip[i]);
    }
    return ip_str.str();
}

