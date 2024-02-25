/**
 * @file BinaryConvert.cpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

#include "../DataConv/Core"

using namespace dataconv;

struct OriginalData : DATACONV_WITH_MULTI_CONVERTER {
    char original_data_char_data;
    short original_data_short_data;
    int original_data_int_data;
    long original_data_long_data;
    float original_data_float_data;
    double original_data_double_data;

    OriginalData()
      : original_data_char_data(0),
        original_data_short_data(0),
        original_data_int_data(0),
        original_data_long_data(0),
        original_data_float_data(0),
        original_data_double_data(0) {}

    OriginalData(char char_data, short short_data, int int_data, long long_data, float float_data, double double_data)
      : original_data_char_data(char_data),
        original_data_short_data(short_data),
        original_data_int_data(int_data),
        original_data_long_data(long_data),
        original_data_float_data(float_data),
        original_data_double_data(double_data) {}

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(OriginalData, original_data_char_data, original_data_short_data, original_data_int_data,
                                             original_data_long_data, original_data_float_data, original_data_double_data);
};

struct TestData : DATACONV_WITH_MULTI_CONVERTER {
	char char_data;
	short short_data;
	int int_data;
	long long_data;
	float float_data;
	double double_data;
    OriginalData original_data;

	TestData() : char_data(0), short_data(0), int_data(0), long_data(0), float_data(0), double_data(0), original_data() {}
    TestData(char char_data, short short_data, int int_data, long long_data, float float_data, double double_data, OriginalData original_data) : char_data(char_data), short_data(short_data), int_data(int_data), long_data(long_data), float_data(float_data), double_data(double_data), original_data(original_data) {}

	DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(TestData, char_data, short_data, int_data, long_data, float_data, double_data, original_data);
};

int main() {
	std::vector<std::uint8_t> bin_data;

    TestData cpp_data{
        1, 2, 3, 4, 5.0f, 6.0, 
        {7, 8, 9, 10, 11.0f, 12.0}
    };

	cpp_data >> bin_data;

	std::cout << "Input:  " << cpp_data << std::endl;
	std::cout << "Output (CSV):  " << cpp_data.toCsv() << std::endl;
	std::cout << "Output (JSON): " << cpp_data.toJsonString() << std::endl;
	std::cout << "Output (Binary): " << to_ordered_hex_string(bin_data) << std::endl;
	// std::cout << "Output: " << to_hex_string(bin_data) << std::endl;
}