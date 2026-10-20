
#include "packetCapture/captureSession.hpp" // To open device
#include "packetCapture/packetCapture.hpp"  // To capture packets

#include <pcap.h> 


int main() 
{
    // Get the device list
    pcap_if_t* alldevs { get_device_list() };
    if (alldevs == nullptr) {
        return 1;
    }

    // Get device choice from user
    pcap_if_t* device { get_device(alldevs) };
    if (device == nullptr) {
        pcap_freealldevs(alldevs);
        return 1;
    }

    // Open a capture session
    pcap_t *handle { open_device(device) };
    if (handle == nullptr) {
        pcap_freealldevs(alldevs);
        return 1;
    }

    // Check the link layer (only support Ethernet for now)
    if(pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
        pcap_freealldevs(alldevs);
        return 1;
    }

    // Capture packets
    run_capture_session(handle);

    // Free the device list 
    pcap_freealldevs(alldevs);

    // Close capture session
    //pcap_close(handle);


    return 0;
}