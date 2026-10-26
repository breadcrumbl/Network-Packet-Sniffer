#pragma once

//Standard library functions
#include <cstddef>      // For std::size_t
#include <cstdint>
#include <vector>

// Function declarations
std::uint16_t read_uint16(const std::uint8_t*& data_ptr);
std::vector<std::uint8_t> read_address(const std::uint8_t*& data_ptr, std::size_t length);
std::uint8_t get_upper_x_bits(const std::uint8_t* data_ptr, int x);
std::uint8_t get_lower_x_bits(const std::uint8_t* data_ptr, int x);
std::uint8_t get_xth_bit(const std::uint8_t* data_ptr, int x);