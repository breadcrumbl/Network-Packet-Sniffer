#include "packetFormat/tcpFormat.hpp"

#include <cstdint>
#include <string>
#include <vector>



// Convert parsed TCP information into formatted TCP information.
FormattedTCP format_tcp(const ParsedTCP& parsed) {
    FormattedTCP formatted {};

    formatted.src_port = std::to_string(parsed.src_port);
    formatted.dest_port = std::to_string(parsed.dest_port);
    formatted.sequence_number = std::to_string(parsed.sequence_number);
    formatted.acknowledgement_number = std::to_string(parsed.acknowledgement_number);
    formatted.data_offset_bytes = std::to_string(parsed.data_offset_bytes);
    formatted.reserved = std::to_string(parsed.reserved);
    formatted.flags = format_tcp_flags(parsed.flags);
    formatted.window_size = std::to_string(parsed.window_size);
    formatted.checksum = std::to_string(parsed.checksum);
    formatted.urgent_pointer = std::to_string(parsed.urgent_pointer);

    return formatted;
}


// Convert TCP flags into readable names.
// Each of the 8 flags are represented by a single bit in the flags byte. 
// The function checks each bit and adds the corresponding flag name to a vector if the bit is set. Finally, it joins the names into a single string.
std::string format_tcp_flags(const std::uint8_t flags) {
    std::vector<std::string> active_flags {};

    if (flags & 0x80) active_flags.push_back("CWR");
    if (flags & 0x40) active_flags.push_back("ECE");
    if (flags & 0x20) active_flags.push_back("URG");
    if (flags & 0x10) active_flags.push_back("ACK");
    if (flags & 0x08) active_flags.push_back("PSH");
    if (flags & 0x04) active_flags.push_back("RST");
    if (flags & 0x02) active_flags.push_back("SYN");
    if (flags & 0x01) active_flags.push_back("FIN");

    if (active_flags.empty()) {
        return "None";
    }

    std::string result {};

    for (const std::string& flag : active_flags) {
        if (!result.empty()) {
            result += ", ";
        }

        result += flag;
    }

    return result;
}