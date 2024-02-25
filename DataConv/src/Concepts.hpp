/**
 * @file Concepts.hpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

#include "Macro.hpp"

DATACONV_NAMESPACE_BEGIN

template <class T, class U>
concept same_as_impl = std::is_same_v<T, U>;

template <class T, class U>
concept same_as = same_as_impl<T, U>&& same_as_impl<U, T>;

template <class From, class To>
concept convertible_to = std::is_convertible_v<From, To>&& requires(std::add_rvalue_reference_t<From> (&f)()) {
	static_cast<To>(f());
};

template <class T, class U>
concept same_as_size = sizeof(T) == sizeof(U);

template <class T>
concept byte_type = sizeof(T) == 1;

template <class T>
concept container_type = std::is_trivially_copyable_v<typename T::value_type>&& requires(T& x) {
	{ x.size() }
	->convertible_to<typename T::size_type>;
	{ x.max_size() }
	->convertible_to<typename T::size_type>;
	{ x.empty() }
	->convertible_to<bool>;
};

template <class T>
concept sequence_container_type = container_type<T>&& requires(T& x) {
	{ x.begin() }
	->convertible_to<typename T::iterator>;
	{ x.end() }
	->convertible_to<typename T::iterator>;
	typename T::value_type;
};

template <class T>
concept dynamic_sequence_container_type = sequence_container_type<T>&& requires(T& x) {
	{ x.capacity() }
	->convertible_to<typename T::size_type>;
	{ x.resize() }
	->convertible_to<typename T::size_type>;
	{ x.resize() }
	->convertible_to<typename T::size_type>;
	{ x.shrink_to_fit() }
	->convertible_to<typename T::size_type>;
};

template <class T>
concept string_type = same_as<std::basic_string<typename T::value_type>, T> ||
					  same_as<std::basic_string<typename T::value_type, typename T::allocator_type>, T>;

template <class T>
concept not_string_sequence_container_type = sequence_container_type<T> && !string_type<T>;

DATACONV_NAMESPACE_END

// 以降マクロ魔術
// clang-format off
#define DATACONV_CODE_GEN_HAS_MEMBER_FUNCTION_CONCEPT_IMPL_TAG dataconv_code_gen_impl_has

#define DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_IMPL_NAME(member_function_name) \
	DATACONV_CODE_GEN_CONCAT(DATACONV_CODE_GEN_HAS_MEMBER_FUNCTION_CONCEPT_IMPL_TAG, member_function_name)

#define DATACONV_DEFINE_HAS_MEMBER_FUNCTION_CONCEPT_IMPL(member_function_name) 				\
template <class T, class R, class... Args> 																			\
concept DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_IMPL_NAME(member_function_name)	\
	= requires(T& x, Args&...args) {														\
	{ x.member_function_name(args...) } 													\
		-> DATACONV_NAMESPACE_BASE_TAG::convertible_to<R>; 	\
};

#define DATACONV_CODE_GEN_HAS_MEMBER_FUNCTION_CONCEPT_TAG dataconv_code_gen_has

#define DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(member_function_name) \
	DATACONV_CODE_GEN_CONCAT(DATACONV_CODE_GEN_HAS_MEMBER_FUNCTION_CONCEPT_TAG, member_function_name)

#define DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT(return_type, member_function_name, ...) 	\
	 DATACONV_DEFINE_HAS_MEMBER_FUNCTION_CONCEPT_IMPL(member_function_name) 							\
	 template<class T> 																										\
	 concept DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(member_function_name) 			\
	 	= DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_IMPL_NAME(member_function_name)<T, return_type, __VA_ARGS__>;
// clang-format on