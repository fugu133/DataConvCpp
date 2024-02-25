/**
 * @file BitOperator.hpp
 * @author fugu133
 * @brief ビット操作機能
 * @version 0.1
 * @date 2024-02-24
 *
 * @copyright Copyright (c) 2024 fugu133
 *
 */

#pragma once

#include <cstddef>
#include <cstring>

#include "Concepts.hpp"
#include "Macro.hpp"

DATACONV_NAMESPACE_BEGIN

namespace detail {

	template <class T>
	concept bit_castable_type_impl = (std::is_arithmetic_v<T> ||
									  std::is_enum_v<T>)&&std::is_trivially_copyable_v<T>&& std::is_standard_layout_v<T>;

	template <class T, class U>
	concept bit_castable_type = bit_castable_type_impl<T>&& bit_castable_type_impl<U>&& same_as_size<T, U>;

	template <class T>
	concept bit_operable_type = bit_castable_type_impl<T>;

	template <std::size_t Size>
	struct sized_integer {
		using type = void;
	};

	template <>
	struct sized_integer<1> {
		using type = std::uint8_t;
	};

	template <>
	struct sized_integer<2> {
		using type = std::uint16_t;
	};

	template <>
	struct sized_integer<4> {
		using type = std::uint32_t;
	};

	template <>
	struct sized_integer<8> {
		using type = std::uint64_t;
	};

	template <std::size_t Size>
	using sized_integer_t = typename sized_integer<Size>::type;
} // namespace detail

/**
 * @brief ビットキャスト (ビット単位でのキャスト)
 * 
 * @remark 値の整合性は保証されない．
 * @tparam To キャスト先の型
 * @tparam From キャスト元の型
 * @param input キャスト元の値
 * @return To キャスト後の値
 */
template <class To, class From>
requires detail::bit_castable_type<To, From> static auto bit_cast(const From& input) noexcept -> To {
	if constexpr (std::is_same_v<To, From>) {
		return input;
	} else {
		To result;
		std::memcpy(&result, &input, sizeof(To));
		return result;
	}
}

/**
 * @brief 1のビット数を数える
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @return std::size_t 1となるビット数
 */
template <detail::bit_operable_type T>
static auto pop_count(const T& value) noexcept -> std::size_t {
	using integer = detail::sized_integer_t<sizeof(T)>;
	std::size_t result = 0;
	integer bit_cast_value = bit_cast<integer>(value);
	for (std::size_t i = 0; i < sizeof(integer) * 8; i++) {
		if (bit_cast_value & (static_cast<integer>(1) << i)) {
			result++;
		}
	}
	return result;
}

/**
 * @brief 偶数パリティ
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @return true 偶数
 * @return false 奇数
 */
template <detail::bit_operable_type T>
static auto even_parity(const T& value) noexcept -> bool {
	return pop_count(value) & 1;
}

/**
 * @brief 奇数パリティ
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @return true 奇数
 * @return false 偶数
 */
template <detail::bit_operable_type T>
static auto odd_parity(const T& value) noexcept -> bool {
	return !even_parity(value);
}

/**
 * @brief 左に循環ビットシフト
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @param count シフト数
 * @return T シフト後の値
 */
template <detail::bit_operable_type T>
static auto rotate_left(const T& value, std::size_t count) noexcept -> T {
	using integer = detail::sized_integer_t<sizeof(T)>;
	integer bit_cast_value = bit_cast<integer>(value);
	integer result = (bit_cast_value << count) | (bit_cast_value >> (sizeof(T) * 8 - count));
	return bit_cast<T>(result);
}

/**
 * @brief 右に循環ビットシフト
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @param count シフト数
 * @return T シフト後の値
 */
template <detail::bit_operable_type T>
static auto rotate_right(const T& value, std::size_t count) noexcept -> T {
	using integer = detail::sized_integer_t<sizeof(T)>;
	integer bit_cast_value = bit_cast<integer>(value);
	integer result = (bit_cast_value >> count) | (bit_cast_value << (sizeof(T) * 8 - count));
	return bit_cast<T>(result);
}

/**
 * @brief ビット反転
 * 
 * @tparam T ビット演算可能な型
 * @param value 対象の値
 * @return T 反転後の値
 */
template <detail::bit_operable_type T>
static auto reverse(const T& value) noexcept -> T {
	using integer = detail::sized_integer_t<sizeof(T)>;
	integer bit_cast_value = bit_cast<integer>(value);

	if constexpr (sizeof(T) == 1) {
		bit_cast_value = (bit_cast_value & 0x55) << 1 | (bit_cast_value & 0xAA) >> 1;
		bit_cast_value = (bit_cast_value & 0x33) << 2 | (bit_cast_value & 0xCC) >> 2;
		bit_cast_value = (bit_cast_value & 0x0F) << 4 | (bit_cast_value & 0xF0) >> 4;
	} else if constexpr (sizeof(T) == 2) {
		bit_cast_value = (bit_cast_value & 0x5555) << 1 | (bit_cast_value & 0xAAAA) >> 1;
		bit_cast_value = (bit_cast_value & 0x3333) << 2 | (bit_cast_value & 0xCCCC) >> 2;
		bit_cast_value = (bit_cast_value & 0x0F0F) << 4 | (bit_cast_value & 0xF0F0) >> 4;
		bit_cast_value = (bit_cast_value & 0x00FF) << 8 | (bit_cast_value & 0xFF00) >> 8;
	} else if constexpr (sizeof(T) == 4) {
		bit_cast_value = (bit_cast_value & 0x55555555) << 1 | (bit_cast_value & 0xAAAAAAAA) >> 1;
		bit_cast_value = (bit_cast_value & 0x33333333) << 2 | (bit_cast_value & 0xCCCCCCCC) >> 2;
		bit_cast_value = (bit_cast_value & 0x0F0F0F0F) << 4 | (bit_cast_value & 0xF0F0F0F0) >> 4;
		bit_cast_value = (bit_cast_value & 0x00FF00FF) << 8 | (bit_cast_value & 0xFF00FF00) >> 8;
		bit_cast_value = (bit_cast_value & 0x0000FFFF) << 16 | (bit_cast_value & 0xFFFF0000) >> 16;
	} else if constexpr (sizeof(T) == 8) {
		bit_cast_value = (bit_cast_value & 0x5555555555555555) << 1 | (bit_cast_value & 0xAAAAAAAAAAAAAAAA) >> 1;
		bit_cast_value = (bit_cast_value & 0x3333333333333333) << 2 | (bit_cast_value & 0xCCCCCCCCCCCCCCCC) >> 2;
		bit_cast_value = (bit_cast_value & 0x0F0F0F0F0F0F0F0F) << 4 | (bit_cast_value & 0xF0F0F0F0F0F0F0F0) >> 4;
		bit_cast_value = (bit_cast_value & 0x00FF00FF00FF00FF) << 8 | (bit_cast_value & 0xFF00FF00FF00FF00) >> 8;
		bit_cast_value = (bit_cast_value & 0x0000FFFF0000FFFF) << 16 | (bit_cast_value & 0xFFFF0000FFFF0000) >> 16;
		bit_cast_value = (bit_cast_value & 0x00000000FFFFFFFF) << 32 | (bit_cast_value & 0xFFFFFFFF00000000) >> 32;
	}

	return bit_cast<T>(bit_cast_value);
}

// template <bit_operable_type T>
// static auto reverse(const T& value) noexcept -> T {
// 	using integer = sized_integer_t<sizeof(T)>;
// 	integer bit_cast_value = bit_cast<integer>(value);
// 	integer result = 0;
// 	for (std::size_t i = 0; i < sizeof(T) * 8; i++) {
// 		result |= ((bit_cast_value >> i) & 1) << (sizeof(T) * 8 - i - 1);
// 	}
// 	return bit_cast<T>(result);
// }

DATACONV_NAMESPACE_END
