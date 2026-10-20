// Paired header
#include "packetPrinter/timePrinter.hpp"
// My other headers
#include "packetPrinter/printConfig.hpp"    // For print_space
// Standard library headers
#include <cstdio>   // For printf
#include <cstring>  // For c_str (for passing strings to printf)
#include <string>


void print_time(const std::string time) {
    // Field specifiers %-ns:
    //  % -> start of specifier
    //  - -> left-aligned
    //  n -> width e.g. 30 chars wide; * takes this an an arg
    //  s -> type (string)
    printf("%-*s", 
        static_cast<int>(time.size() + PrintConfig::print_space), time.c_str());
}