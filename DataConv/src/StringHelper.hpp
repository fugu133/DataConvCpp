/**
 * @file StringHelper.hpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstddef>
#include <iomanip>
#include <ios>
#include <sstream>

#include "BitOperator.hpp"
#include "Concepts.hpp"
#include "EndianConverter.hpp"
#include "Macro.hpp"

DATACONV_NAMESPACE_BEGIN

struct StringStreamHelper {
	template <typename T>
	static auto reset(std::basic_stringstream<T>& s) {
		s.str(" ");
		s.clear(std::basic_stringstream<T>::goodbit);
	}

	template <typename T>
	static auto reset(std::basic_istringstream<T>& s) {
		s.str(" ");
		s.clear(std::basic_istringstream<T>::goodbit);
	}
};

struct array_stream_policy {
	static constexpr char* prefix = (char*)"";
	static constexpr char* suffix = (char*)"";
	static constexpr char* delimiter = (char*)" ";
};

struct hex_stream_policy {
	static constexpr char* prefix = (char*)"0x";
	static constexpr std::size_t width = 2;
	static constexpr char fill = '0';
	static constexpr bool uppercase = true;
	static constexpr bool split = true;
};

template <class T>
  requires std::is_arithmetic_v<T> || std::is_enum_v<T> static auto to_hex_string(const T& value) noexcept -> std::string {
	if constexpr (sizeof(T) == 1) {
		return to_hex_string(static_cast<std::uint32_t>(value));
	} else {
		std::stringstream ss;
		if (hex_stream_policy::uppercase) {
			ss << hex_stream_policy::prefix << std::setw(hex_stream_policy::width) << std::setfill(hex_stream_policy::fill)
			   << std::uppercase << std::hex << value;
		} else {
			ss << hex_stream_policy::prefix << std::setw(hex_stream_policy::width) << std::setfill(hex_stream_policy::fill) << std::hex
			   << value;
		}
		return ss.str();
	}
}

template <sequence_container_type T>
  requires std::is_arithmetic_v<typename T::value_type> ||
  std::is_enum_v<typename T::value_type> static auto to_hex_string(const T& value) noexcept -> std::string {
	std::stringstream ss;
	ss << array_stream_policy::prefix;
	for (std::size_t i = 0; i < value.size(); i++) {
		ss << to_hex_string(value[i]);
		if (i != value.size() - 1) {
			ss << array_stream_policy::delimiter;
		} else {
			ss << array_stream_policy::suffix;
		}
	}
	return ss.str();
}

template <class T>
  requires std::is_arithmetic_v<T> || std::is_enum_v<T> static auto to_ordered_hex_string(const T& value) noexcept -> std::string {
	T big_endian_value = to_big_endian(value);

	if constexpr (sizeof(T) == 1) {
		return to_hex_string(static_cast<std::uint32_t>(big_endian_value));
	} else {
		std::stringstream ss;

		ss << hex_stream_policy::prefix;

		for (std::size_t i = 0; i < sizeof(T); i++) {

			if (hex_stream_policy::split && i != 0) {
				ss << hex_stream_policy::prefix;
			}

			if (hex_stream_policy::uppercase) {
				ss << std::setw(hex_stream_policy::width) << std::setfill(hex_stream_policy::fill) << std::uppercase << std::hex
				   << static_cast<std::uint64_t>(reinterpret_cast<const std::uint8_t*>(&big_endian_value)[i]);
			} else {
				ss << std::setw(hex_stream_policy::width) << std::setfill(hex_stream_policy::fill) << std::hex
				   << static_cast<std::uint64_t>(reinterpret_cast<const std::uint8_t*>(&big_endian_value)[i]);
			}

			if (hex_stream_policy::split && i != sizeof(T) - 1) {
				ss << array_stream_policy::delimiter;
			}
		}
		return ss.str();
	}
}

template <sequence_container_type T>
  requires std::is_arithmetic_v<typename T::value_type> ||
  std::is_enum_v<typename T::value_type> static auto to_ordered_hex_string(const T& value) noexcept -> std::string {
	std::stringstream ss;
	ss << array_stream_policy::prefix;
	for (std::size_t i = 0; i < value.size(); i++) {
		ss << to_ordered_hex_string(value[i]);
		if (i != value.size() - 1) {
			ss << array_stream_policy::delimiter;
		} else {
			ss << array_stream_policy::suffix;
		}
	}
	return ss.str();
}

static inline auto check_hex_range_string(const char& c) -> bool {
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static inline auto hex_string_to_integer(const char* start, char** end, unsigned int digit = 16) -> std::uint64_t {
	std::uint64_t result = 0;

	char* sp = (start[0] == '0' && (start[1] == 'x' || start[1] == 'X') ? const_cast<char*>(start) + 2 : const_cast<char*>(start));
	char* rp = sp;

	while (*rp != '\0' && rp - sp < digit) {
		if (*rp == '\0') {
			break;
		}

		if (*rp >= '0' && *rp <= '9') {
			result <<= 4;
			result += *rp - '0';
		} else if (*rp >= 'a' && *rp <= 'f') {
			result <<= 4;
			result += *rp - 'a' + 10;
		} else if (*rp >= 'A' && *rp <= 'F') {
			result <<= 4;
			result += *rp - 'A' + 10;
		} else {
			break;
		}
		++rp;
	}

	if (end) *end = const_cast<char*>(rp);

	return result;
}

template <class T>
requires std::is_integral_v<T> static auto hex_string_to_integer(const char* start, char** end) noexcept -> T {
	return hex_string_to_integer(start, end, sizeof(T) * 2);
}

template <class T>
requires std::is_integral_v<T> static auto hex_string_to_integer(const std::string& hex_str) noexcept -> T {
	return hex_string_to_integer(hex_str.c_str(), nullptr, sizeof(T) * 2);
}

template <sequence_container_type T>
requires std::is_integral_v<typename T::value_type> static auto hex_string_to_array(const char* start, T& array) noexcept -> std::size_t {
	char* read_ptr = const_cast<char*>(start);
	char* end_ptr = nullptr;
	std::size_t write_idx = 0;
	typename T::value_type hex_data = 0;

	while (*read_ptr != '\0') {

		hex_data = hex_string_to_integer<typename T::value_type>(read_ptr, &end_ptr);
		if (end_ptr != read_ptr) {
			array.push_back(hex_data);
			read_ptr = end_ptr;
			write_idx++;
		} else {
			read_ptr++;
		}
	}

	return write_idx;
}

static inline auto joint(const std::string& left, const std::string& right, const std::string& delimiter = " ") -> std::string {
	if (left.empty() && right.empty()) {
		return std::string();
	} else if (left.empty()) {
		return right;
	} else if (right.empty()) {
		return left;
	} else {
		return left + delimiter + right;
	}
}

DATACONV_NAMESPACE_END
