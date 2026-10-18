
### Choosing a Device
- pcap_findalldevs_ex() fills linked list alldevs with all availble devices (interfaces) on machine
- The program prints this list.
- Gets the chosen device from the user using scanf_s.
pcap_open() opens the device into a pcap_t structure pwith pointer adhandle. This handle must be later closed with pcap_close()
- The linked list of devices, alldevices, is freed.

### Capturing Packets
- pcap_next_ex() retreives a packet with a direct call. It's arguments are the pointer to the device being captured from (adhandle), the address of the pointer to the packet header, which contains information on the packet like the timestamp and the length and the actual data of the packet including all the protocol headers (&header), and the address of the pointer to where the packet data will be stored (&pkt_data).
    - Continues capyuring packets until and error occurs, the end of a capture file is reached (for offline capture), or programmed ended i.e. with ctrl+c 
    

## Program Structure
File	Responsibility
main.cpp	Entry point; coordinates the program
packetCapture.cpp	Selects interfaces, opens captures and receives packets
packetParser.cpp	Decodes Ethernet, IP, TCP and UDP headers
packetAnalyser.cpp	Counts packets, tracks endpoints and summarises traffic

```
packet-analyser/
├── Makefile
├── src/
│   ├── main.cpp
│   ├── packetCapture.cpp
│   ├── packetParser.cpp
│   └── packetAnalyser.cpp
└── include/
    ├── packetCapture.hpp
    ├── packetParser.hpp
    └── packetAnalyser.hpp
```

packetCapture
- pcap_if_t* get_device_list(): returns a pointer to a linked list of available devices (interfaces / adapters) if successful, otherwise returns nullptr
- pcap_if_t* get_device(pcap_if_t*& alldevs): takes in user input from the console to choose a device from the device list and returns a pointer to that device is successful, other returns nullptr
- pcap_t* open_device(pcap_if_t*& device): opens a capture session on the device, which continuously listens, captures, and processes packets until user ends program (e.g. ctrl+c) or a capture error occurs