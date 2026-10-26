// Paired header
#include "packetCapture/captureSession.hpp"
// My other headers
#include "packetCapture/packetCapture.hpp"  // For CapturedPacket struct and capture_packet()
#include "packetFormat/packetFormat.hpp"    // For FormattedPacket struct
#include "packetParser/packetParser.hpp"    // For ParsedPacket struct
#include "packetPrinter/packetPrinter.hpp"  // To print formatted packet
// 3rd party headers
#include <pcap.h> 
// Standard library headers
#include <cstdio>

#include <iostream>     // For debugging

// Return a pointer to device list if successful, nullptr otherwise
pcap_if_t* get_device_list() {
    pcap_if_t *alldevs { nullptr };
    char errbuf[PCAP_ERRBUF_SIZE]{};

    // Retrieve the device list from the local machine
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING,
        NULL /* auth is not needed */,
        &alldevs, errbuf) == -1) {
        fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
        return nullptr;
    }
    return alldevs;
}

// Function that accepts list of available devices as an argument, prints them, then gets the user to choose one
// Returns a pointer to the device if succesfull and nullptr if not
pcap_if_t* get_device(pcap_if_t*& alldevs) {
    // Print the list of available devices
    int device_count { 0 };
    for(pcap_if_t* d { alldevs }; d != nullptr; d = d->next) {
        printf("%d. %s", ++device_count, d->name); {}
        if (d->description) {
            printf("(%s)\n", d->description);
        }
        else {
            printf("(No description available)\n");
        }
    }
    if (device_count == 0) {
        printf("\nNo interfaces found! Make sure Npcap is installed.\n");
        return nullptr;
    }

    // Get user input
    int input_number {};
    printf("Enter the interface number (1-%d):",device_count);
    scanf_s("%d", &input_number);
    if(input_number < 1 || input_number > device_count) {
        printf("\nInterface number out of range.\n");
        return nullptr;
    }

    // Jump to the selected adapter and return the pointer to it
    pcap_if_t* device_ptr { alldevs };
    for(int i { 0 }; i < input_number - 1; ++i) {
        device_ptr = device_ptr->next;
    }
    return device_ptr;
}

// Open device using pcap_open. Return 
pcap_t* open_device(pcap_if_t*& device) {
    pcap_t *handle { nullptr };
    char errbuf[PCAP_ERRBUF_SIZE]{};
    if ((handle = pcap_open(device->name, // name of the device
            65536, // portion of the packet to capture
                    // 65536 guarantees that the whole packet will
                    // be captured on all the link layers
            PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
            1000, // read timeout
            NULL, // authentication on the remote machine
            errbuf // error buffer
            )) == NULL) {
        fprintf(stderr, "\nUnable to open the adapter. %s is not supported by Npcap\n", device->name);
        return nullptr;
    }
    printf("\nListening on %s...\n", device->description);
    return handle;
}

// The capture session captures and processes packets
void run_capture_session(pcap_t*& handle) {
    while (true) {

    auto raw { capture_packet(handle) };
    if (!raw) {
        // No packet returned -> retry
        continue;
    }

    ParsedPacket parsed { parse_packet(*raw) };
    FormattedPacket formatted { format_packet(parsed) };
    print_packet(formatted);
    //std::cout << static_cast<int>(parsed.ipv4.ttl) << std::endl;
    // std::cout << "Formatted TTL: [" << formatted.ipv4.ttl << "]\n";
    }
}