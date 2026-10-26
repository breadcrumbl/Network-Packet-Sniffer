// Paired header
#include "packetPrinter/timePrinter.hpp"
// My other headers
#include "packetPrinter/printConfig.hpp"    // For print_space
// Standard library headers
#include <iomanip>      // For formatting output
#include <iostream>     // For output
#include <string>



void print_time(const std::string time) {
    std::cout << std::left
          << std::setw(static_cast<int>(time.size() + PrintConfig::print_space))
          << time;
}