#pragma once
// 3rd party library headers
#include <pcap.h>
// Standard library headers
#include <vector>

/*
* A Packet struct contains the header (structure shown below) and the packet data
* struct pcap_pkthdr {
*	struct timeval ts;	// time stamp 
*	bpf_u_int32 caplen;	// length of portion present 
*	bpf_u_int32 len;	// length of this packet (off wire)
* };
*/
struct Packet {
    pcap_pkthdr header {};
    std::vector<u_char> data {};
};

// Function declarations
pcap_if_t* get_device_list();
pcap_if_t* get_device(pcap_if_t*& alldevs);
pcap_t* open_device(pcap_if_t*& device);
void capture_packets(pcap_t*& handle);
