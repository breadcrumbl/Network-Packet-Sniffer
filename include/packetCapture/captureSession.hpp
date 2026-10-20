#pragma once
// 3rd party library headers
#include <pcap.h>
// Standard library headers
#include <chrono>   // For timestamp
#include <vector>   // For data

// Function declarations
pcap_if_t* get_device_list();
pcap_if_t* get_device(pcap_if_t*& alldevs);
pcap_t* open_device(pcap_if_t*& device);
void run_capture_session(pcap_t*& handle);