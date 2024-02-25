/**
 * @file EndianConverter.hpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-24
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @file EndianC.hpp
 * @author fugu133
 * @brief エンディアン変換
 * @version 0.1
 * @date 2023-05-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cstddef>

#include "Concepts.hpp"
#include "Macro.hpp"

DATACONV_NAMESPACE_BEGIN

template <class T>
concept endian_convertible_type = std::is_arithmetic_v<T> || std::is_enum_v<T>;

template <class T>
concept endian_convertible_sequence_container_type = endian_convertible_type<typename T::value_type>&& sequence_container_type<T>;

enum class endian {
#ifdef _WIN32
	little = 0,
	big = 1,
	native = little
#else
	little = __ORDER_LITTLE_ENDIAN__,
	big = __ORDER_BIG_ENDIAN__,
	native = __BYTE_ORDER__
#endif
};

static constexpr auto which() noexcept -> endian {
	return endian::native;
}

static constexpr auto is_little_endian() noexcept -> bool {
	return endian::native == endian::little;
}

static constexpr auto is_big_endian() noexcept -> bool {
	return not is_little_endian();
}

template <endian_convertible_type T>
static auto reverse(const T& input, T& output) noexcept -> void {
	for (std::size_t i = 0; i < sizeof(T); i++) {
		reinterpret_cast<uint8_t*>(&output)[i] = reinterpret_cast<const uint8_t*>(&input)[sizeof(T) - i - 1];
	}
}

template <endian_convertible_type T>
static auto reverse(const T& value) noexcept -> T {
	T result = static_cast<T>(0);
	reverse(value, result);
	return result;
}

template <endian_convertible_type T>
static auto to_big_endian(const T& input, T& output) noexcept -> void {
	if constexpr (is_little_endian()) {
		reverse(input, output);
	} else {
		output = input;
	}
}

template <endian_convertible_type T>
static auto to_big_endian(const T& value) noexcept -> T {
	if constexpr (is_little_endian()) {
		return reverse(value);
	} else {
		return value;
	}
}

template <endian_convertible_type T>
static auto to_little_endian(const T& input, T& output) noexcept -> void {
	if constexpr (is_big_endian()) {
		reverse(input, output);
	} else {
		output = input;
	}
}

template <endian_convertible_type T>
static auto to_little_endian(const T& value) noexcept -> T {
	if constexpr (is_big_endian()) {
		return reverse(value);
	} else {
		return value;
	}
}

template <endian_convertible_sequence_container_type T>
static auto to_big_endian(const T& input, T& output) -> void {
	if constexpr (dynamic_sequence_container_type<T>) {
		if (output.size() < input.size()) {
			output.resize(input.size());
		}
	}

	for (std::size_t i = 0; i < input.size(); i++) {
		to_big_endian(input[i], output[i]);
	}
}

template <endian_convertible_sequence_container_type T>
static auto to_big_endian(const T& input) -> T {
	if constexpr (dynamic_sequence_container_type<T>) {
		T output(input.size());
		to_big_endian(input, output);
		return output;
	} else {
		T output;
		to_big_endian(input, output);
		return output;
	}
}

template <endian_convertible_sequence_container_type T>
static auto to_little_endian(const T& input, T& output) -> void {
	if constexpr (dynamic_sequence_container_type<T>) {
		if (output.size() < input.size()) {
			output.resize(input.size());
		}
	}

	for (std::size_t i = 0; i < input.size(); i++) {
		to_little_endian(input[i], output[i]);
	}
}

template <endian_convertible_sequence_container_type T>
static auto to_little_endian(const T& input) -> T {
	if constexpr (dynamic_sequence_container_type<T>) {
		T output(input.size());
		to_little_endian(input, output);
		return output;
	} else {
		T output;
		to_little_endian(input, output);
		return output;
	}
}

DATACONV_NAMESPACE_END