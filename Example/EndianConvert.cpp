/**
 * @file EndianConvert.cpp
 * @author Kaiji Takeuchi
 * @brief
 * @version 0.1
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

#include "../DataConv/src/EndianConverter.hpp"

using namespace dataconv;

int main() {
	std::uint32_t a = 0x21436587;
	std::uint32_t b = to_big_endian(a);
	std::cout << std::hex << a << std::endl;
	std::cout << std::hex << b << std::endl;
	return 0;
}