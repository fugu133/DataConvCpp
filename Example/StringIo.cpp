/**
 * @file StringIo.cpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024 fugu133
 *
 */

#include <iostream>

#include "../DataConv/Core"

using namespace dataconv;

int main() {
	const std::string in_str = "0x12345678";
	const std::uint32_t hex_data = hex_string_to_integer<std::uint32_t>(in_str);
	std::cout << "Input:  " << in_str << std::endl;
	std::cout << "Output: " << to_hex_string(hex_data) << std::endl;

	return 0;
}