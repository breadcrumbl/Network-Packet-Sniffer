// Paired header
#include "packetParser/parsingFunctions.hpp"

//Standard library functions
#include <cstddef>      // For std::size_t
#include <cstdint>
#include <vector>

// Reads info stored as 2 bytes in Big-Endian order to a single uint16_t value then advances the ptr to the next byte
std::uint16_t read_uint16(const std::uint8_t*& data_ptr) {
    uint16_t value { static_cast<std::uint16_t>( (data_ptr[0] << 8) | data_ptr[1] ) };
    data_ptr +=2;
    return value;
}

// Reads N bytes into N elements of a vector and updates ptr
std::vector<std::uint8_t> read_address(const std::uint8_t*& data_ptr, std::size_t length) {
    std::vector<std::uint8_t> address(length);
    for (std::size_t i { 0 }; i < length; ++i) {
        address[i] = *data_ptr++;
    }
    return address;
}

// Right-shift by (8-x)
std::uint8_t get_upper_x_bits(const std::uint8_t* data_ptr, int x) {
    return static_cast<std::uint8_t>( *data_ptr >> (8 - x) );
}

// Apply mask covering x bits; create mask by shifting 1 to the left by x then subtracting 1
// e.g. for a mask of 3 (0111), do 1 << 4 -> 1000; then -1 -> 0111 
std::uint8_t get_lower_x_bits(const std::uint8_t* data_ptr, int x) {
    return static_cast<std::uint8_t>( *data_ptr & ((1U << x) - 1) );
}

// Get xth bit from left by right-shift (x-1) then apply mask of 1 (0001)
std::uint8_t get_xth_bit(const std::uint8_t* data_ptr, int x) {
    return static_cast<std::uint8_t>( (*data_ptr >> x) & 1U );
}


