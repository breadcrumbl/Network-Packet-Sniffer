// Paired header
#include "packetCapture/packetCapture.hpp"
// My other headers

// 3rd party headers
#include <pcap.h>   // For pcap_next_ex()
// Standard library headers
#include <chrono>   // For timestamp
#include <optional> // For std::optional


std::optional<CapturedPacket> capture_packet(pcap_t* handle)
{
    /*
    * pcpap_next_ex() returns       ->     while() loop behaviour
    *     1: packet captured        ->     process packet (print details)
    *     0: timeout                ->     keep listening
    *     -1: capture error         ->     break out of loop and report error
    *     -2: end of file for an offline capture    ->    break out of loop 
    * pcap_next_ex() paramaters:
    *      handle ->  
    *      &header -> address of a pointer that Npcap sets to the packet's metadata
    *      &pkt_data -> Address of a pointer that Npcap sets to the packet's raw bytes
    */
    pcap_pkthdr* header { nullptr };
    const u_char* pkt_data { nullptr };
    int res { pcap_next_ex(handle, &header, &pkt_data) };
    // Timeout: no packet available yet.
    if (res == 0) {
        return std::nullopt;
    }
    // Capture error or end of offline capture
    if (res == -1 || res == -2) {
        return std::nullopt;
    }

    // Convert Npcap metadata into our own C++ types
    /*
    * Relevant Npcap structures
    * struct pcap_pkthdr {
    *	struct timeval ts;	// time stamp 
    *	bpf_u_int32 caplen;	// length of portion present i.e. how many bytes captured
    *	bpf_u_int32 len;	// length of this packet (off wire) i.e. original length reported; can be greater than caplen due to truncation
    * };
    * struct timeval {
    *	long tv_sec;    // Whole seconds    
    *	long tv_usec;   // Additional microseconds
    * };
    */
    CapturedPacket raw {};
    // Creating the timestamp
    // General knowledge: 
    //  The Unix epoch is a fixed point in time (1 January 1970 at 00:00:00 UTC)
    //  Computers often represent timestamps as the number of seconds elasped fromt this point (i.e. as a duration)
    // How the program works:
    //  1. chrono::seconds and microsends -> Wraps the seconds and microsends in header in a C++ duration
    //  2. adds the two together
    //  3. Constructs a time point from the resulting duration since the clock's epoch
    raw.time = std::chrono::system_clock::time_point {
        std::chrono::seconds { header->ts.tv_sec } +
        std::chrono::microseconds { header->ts.tv_usec }
    };
    raw.captured_length = header->caplen;
    raw.original_length = header->len;
    /*
    * This statement fills the packet data vector with the bytes captured. Breakdown:
    *   assign(first, last): accepts a range of elements and replaces the vector's contents with copies of those elements
    *   pkt_data: points to the first byte of the data
    *   header->caplen: number of bytes captured
    *   pkt_data + header->caplen: pointer just past end of of data (pointer arithmetic)
    */
    raw.data.assign(pkt_data, pkt_data + header->caplen);

    return raw;
}
