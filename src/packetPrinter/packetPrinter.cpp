// Paired header
#include "packetPrinter/packetPrinter.hpp"
// My other headers
#include "packetFormat/packetFormat.hpp"    // For FormattedPacket struct
#include "packetPrinter/ethernetPrinter.hpp"
#include "packetPrinter/ipPrinter.hpp"
#include "packetPrinter/tcpPrinter.hpp"
#include "packetPrinter/udpPrinter.hpp"
#include "packetPrinter/timePrinter.hpp"
// Standard library headers



void print_packet(const FormattedPacket& formatted) {
    // Print time
    //print_time(formatted.time);

    // Print ethernet
    /* STUDY:
    ptr->ethernet;       // Access Ethernet pointer through an object pointer
    formatted.ethernet;  // Access Ethernet pointer through an object reference
    *formatted.ethernet; // Access the actual Ethernet object
    */
    if (formatted.ethernet != nullptr) {
        //print_ethernet(*formatted.ethernet);
    }

    // Print IP layer
    if (formatted.ipv4 != nullptr) {
        //print_ipv4(*formatted.ipv4);
    }

    // Print TCP/UDP
    if (formatted.udp != nullptr) {
        //print_udp(*formatted.udp);
    }
    if (formatted.tcp != nullptr) {
        print_tcp(*formatted.tcp);
    }

}