# pragma once

#include "packetParser/ipParser.hpp"    // For ParsedIPv4 struct

#include <string>

struct FormattedIPv4 {
    std::string version {};                
    std::string header_length_bytes {};    
    std::string dscp {};                   
    std::string ecn {};                    
    std::string total_length_bytes {};    
    std::string id {};                    
    std::string reserved_flag {};          
    std::string df_flag {};                
    std::string mf_flag {};                
    std::string fragment_offset_bytes {};       
    std::string ttl {};                    
    std::string protocol {};               
    std::string header_checksum {};        
    std::string src_ip {};  
    std::string dest_ip {}; 
    // std::string options {};     TO-DO
};

FormattedIPv4 format_ipv4(const ParsedIPv4& parsed);
std::string ip_protocol_string(std::uint8_t protocol);
std::string ipv4_to_string(const std::vector<std::uint8_t>& ip);