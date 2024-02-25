/**
 * @file DataConverter.hpp
 * @author fugu133
 * @brief データ変換機能
 * @version 0.1
 * @date 2024-02-25
 * 
 * @copyright Copyright (c) 2024 fugu133
 * 
 */


#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "../../Json/json.hpp"
#include "Concepts.hpp"
#include "EndianConverter.hpp"
#include "Exception.hpp"
#include "Macro.hpp"
#include "StringHelper.hpp"

// 通常コード

DATACONV_NAMESPACE_BEGIN

using namespace nlohmann;

/**
 * @brief 出力文字列のデリミタを指定するインターフェース
 *
 */
struct DelimiterPolicyInterface {
    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ
     */
	auto operator()() const -> std::string { return getDelimiter(); }
	
    /**
     * @brief 末尾にデリミタを追加
     * 
     * @param input 入力文字列
     * @return std::string 出力文字列
     */
    auto operator()(const std::string& input) const -> std::string { return input + getDelimiter(); }

  protected:
	
    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ
     */
    virtual auto getDelimiter() const -> std::string = 0;
};

/**
 * @brief SSV (Space-Separated Values) 形式を指定するポリシー
 *
 */
struct SsvFormatPolicy : public DelimiterPolicyInterface {
	static constexpr char* delimiter = (char*)" ";

  protected:

    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ " "
     */
	auto getDelimiter() const -> std::string override { return delimiter; }
};

/**
 * @brief CSV (Comma-Separated Values) 形式を指定するポリシー
 *
 */
struct CsvFormatPolicy : public DelimiterPolicyInterface {
	static constexpr char* delimiter = (char*)",";

  protected:

    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ ","
     */
	auto getDelimiter() const -> std::string override { return delimiter; }
};

/**
 * @brief TSV (Tab-Separated Values) 形式を指定するポリシー
 *
 */
struct TsvFormatPolicy : public DelimiterPolicyInterface {
	static constexpr char* delimiter = (char*)"\t";

  protected:
    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ "\t"
     */
	auto getDelimiter() const -> std::string override { return delimiter; }
};

/**
 * @brief シーケンスコンテナのヘッダフォーマット
 *
 */
struct ArrayHeaderFormatPolicy {
	static constexpr char* prefix = (char*)"[";
	static constexpr char* suffix = (char*)"]";

    /**
     * @brief ヘッダを生成
     * 
     * @param header_name ヘッダ名
     * @param id コンテナのインデックス
     * @return std::string ヘッダ文字列
     */
	auto operator()(const std::string& header_name, std::size_t id = 0) { return header_name + prefix + std::to_string(id) + suffix; }
};

/**
 * @brief オブジェクトメンバのヘッダフォーマット
 *
 */
struct MemberHeaderFormatPolicy : public DelimiterPolicyInterface {
	static constexpr char* delimiter = (char*)".";

    /**
     * @brief ヘッダを生成
     * 
     * @param object_name オブジェクト名
     * @param member_name メンバ名
     * @return std::string ヘッダ文字列
     */
	auto operator()(const std::string& object_name, const std::string& member_name) { return object_name + delimiter + member_name; }

  protected:
    /**
     * @brief デリミタを取得
     * 
     * @return std::string デリミタ "."
     */
	auto getDelimiter() const -> std::string override { return delimiter; }
};

/**
 * @brief データ変換インターフェース
 *
 */
struct StringConverterInterface {

    /**
     * @brief 文字列に変換
     * 
     * @param delimiter デリミタ
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const 文字列
     */
	virtual auto toString(const std::string& delimiter = SsvFormatPolicy::delimiter, bool inc_end = false) const -> std::string = 0;
	
    /**
     * @brief SSV文字列に変換
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const SSV文字列
     */
    auto toSsv(bool inc_end = false) -> std::string const { return toString(SsvFormatPolicy::delimiter, inc_end); }

    /**
     * @brief TSV文字列に変換
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const TSV文字列
     */
	auto toTsv(bool inc_end = false) -> std::string const { return toString(TsvFormatPolicy::delimiter, inc_end); }
	
    /**
     * @brief CSV文字列に変換
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const CSV文字列
     */
    auto toCsv(bool inc_end = false) -> std::string const { return toString(CsvFormatPolicy::delimiter, inc_end); }
	
    /**
     * @brief ヘッダを生成
     * 
     * @param delimiter デリミタ
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const ヘッダ文字列
     */
    virtual auto makeHeader(const std::string& delimiter = SsvFormatPolicy::delimiter, bool inc_end = false) const -> std::string = 0;
	
    /**
     * @brief SSVヘッダを生成
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const SSVヘッダ文字列
     */
    auto makeSsvHeader(bool inc_end = false) const -> std::string { return makeHeader(SsvFormatPolicy::delimiter, inc_end); }
	
    /**
     * @brief TSVヘッダを生成
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const TSVヘッダ文字列
     */
    auto makeTsvHeader(bool inc_end = false) const -> std::string { return makeHeader(TsvFormatPolicy::delimiter, inc_end); }
	
    /**
     * @brief CSVヘッダを生成
     * 
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string const CSVヘッダ文字列
     */
    auto makeCsvHeader(bool inc_end = false) const -> std::string { return makeHeader(CsvFormatPolicy::delimiter, inc_end); }
};

DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT(std::string, toString, std::string, bool);

/**
 * @brief 文字列変換機能を持つかを示す制約
 * 
 * @tparam T 制約対象の型
 */
template <class T>
concept HasToString = DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(toString)<T>;

DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT(std::string, makeHeader, std::string&, bool);

/**
 * @brief ヘッダ生成機能を持つかを示す制約
 * 
 * @tparam T 制約対象の型
 */
template <class T>
concept HasMakeHeader = DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(makeHeader)<T>;

/**
 * @brief 文字列変換
 *
 */
struct StringConverter {
    /**
     * @brief 文字列に変換
     * 
     * @tparam T 変換対象の型
     * @param value 変換対象の値
     * @param delimiter デリミタ文字
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string 変換後の文字列
     */
	template <class T>
	static auto toString(const T& value, [[maybe_unused]] const std::string& delimiter = SsvFormatPolicy::delimiter,
						 [[maybe_unused]] bool inc_end = false) -> std::string {
		// 型による分岐
		if constexpr (string_type<T>) {
			return inc_end ? value + delimiter : value;
		}
		// bool型
		else if constexpr (std::is_same_v<T, bool>) {
			return toString(std::string{value ? "true" : "false"}, delimiter, inc_end);
		}
		// 浮動小数型
		else if constexpr (std::is_floating_point_v<T>) {
			static char str[32];

			if (inc_end) {
				std::sprintf(&str[0], "%.6e%s", value, delimiter.c_str());
			} else {
				std::sprintf(&str[0], "%.6e", value);
			}

			return std::string{str};
		}
		// 数値型
		else if constexpr (std::is_arithmetic_v<T>) {
			return inc_end ? std::to_string(value) + delimiter : std::to_string(value);
		}
		// (スコープ付き)列挙型
		else if constexpr (std::is_enum_v<T>) {
			return toString(static_cast<std::underlying_type_t<T>>(value), delimiter, inc_end);
		}
		// std::array, std::vector等のコンテナ型
		else if constexpr (not_string_sequence_container_type<T>) {
			std::string str_value;
			str_value.reserve(64);
			for (size_t i = 0; i < value.size(); i++) {
				str_value += toString(value[i]);
				if (i != value.size() - 1 || inc_end) {
					str_value += delimiter;
				}
			}
			return str_value;
			// toStringメンバを持ったオブジェクト型
		} else if constexpr (std::is_base_of_v<StringConverterInterface, T> || HasToString<T>) {
			return value.toString(delimiter, inc_end);
			// 変換方法が定義されていない型
		} else {
			throw ConvertException("Not supported type", ConvertException::NotSupportedTypeError);
			return {"\0"};
		}
	}

    /**
     * @brief ヘッダを生成
     * 
     * @tparam T 変換対象の型
     * @param header_name ヘッダ名
     * @param obj 変換対象の値
     * @param delimiter デリミタ文字
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string ヘッダ文字列
     */
	template <class T>
	static auto makeHeader(const std::string& header_name, [[maybe_unused]] const T& obj,
						   const std::string& delimiter = SsvFormatPolicy::delimiter, bool inc_end = false) -> std::string {

		std::string str_head;

		if constexpr (string_type<T> || std::is_same_v<T, bool> || std::is_arithmetic_v<T> || std::is_enum_v<T>) {
			str_head += header_name;
			if (inc_end) {
				str_head += delimiter;
			}
			return str_head;
		} // std::array, std::vector等のコンテナ型
		else if constexpr (not_string_sequence_container_type<T>) {
			for (size_t i = 0; i < obj.size(); i++) {
				str_head += ArrayHeaderFormatPolicy{}(header_name, i);
				if (i != obj.size() - 1 || inc_end) {
					str_head += delimiter;
				}
			}
			return str_head;
		} // toStringメンバを持ったオブジェクト型
		else if constexpr (std::is_base_of_v<StringConverterInterface, T> || HasMakeHeader<T>) {
			return obj.makeHeader(delimiter, inc_end);
		} else { // 変換方法が定義されていない型
			throw ConvertException("Not supported type", ConvertException::NotSupportedTypeError);
			return {"\0"};
		}
	}

    /**
     * @brief TとUを文字列変換連結
     * 
     * @tparam T 左辺の型
     * @tparam U 右辺の型
     * @param r 左辺の値
     * @param l 右辺の値
     * @param delimiter デリミタ文字
     * @param inc_end 末尾にデリミタを含めるか
     * @return std::string 変換連結した文字列
     */
	template <class T, class U>
	static auto concatenation(const T& r, const U& l, const std::string& delimiter = SsvFormatPolicy::delimiter, bool inc_end = false)
	  -> std::string {
		return {tostring(r, delimiter, true) + tostring(l, delimiter, inc_end)};
	}
};

DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT(std::size_t, toBinary, std::uint8_t*, std::size_t);

/**
 * @brief バイナリシリアライズ機能を持つかを示す制約
 * 
 * @tparam T 制約対象の型
 */
template <class T>
concept HasToBinary = DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(toBinary)<T>;

DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT(std::size_t, fromBinary, std::uint8_t*, std::size_t);

/**
 * @brief バイナリデシリアライズ機能を持つかを示す制約
 * 
 * @tparam T 制約対象の型
 */
template <class T>
concept HasFromBinary = DATACONV_CODE_GEN_RESULT_HAS_MEMBER_FUNCTION_CONCEPT_NAME(fromBinary)<T>;

/**
 * @brief バイナリ変換インターフェース
 *
 */
struct BinaryConverterInterface {
	
    /**
     * @brief バイナリサイズを取得
     * 
     * @return std::size_t サイズ
     */
    virtual auto size() const -> std::size_t = 0;

    /**
     * @brief バイナリに変換
     * 
     * @remark 名前解決できないので継承先でusing宣言すること
     * @param output 出力データ
     * @param offset オフセット
     * @return std::size_t 変換後のサイズ
     */
	virtual auto toBinary(std::uint8_t* output, std::size_t offset = 0) const -> std::size_t = 0;

	/**
     * @brief バイナリにシリアライズ
     * 
     * @param output 出力データ
     * @param offset オフセット
     * @return std::size_t 変換後のサイズ
     */
	auto toBinary(std::vector<std::uint8_t>& output, std::size_t offset = 0) const -> std::size_t {
		if (output.size() < size() + offset) {
			output.resize(size() + offset);
		}
		return toBinary(output.data(), offset);
	}

    /**
     * @brief バイナリからデシリアライズ
     * 
     * @remark 名前解決できないので継承先でusing宣言すること
     * @param data 入力データ
     * @param offset オフセット
     * @return std::size_t 変換後のサイズ
     */
	virtual auto fromBinary(const std::uint8_t* data, std::size_t offset = 0) -> std::size_t = 0;

    /**
     * @brief バイナリからデシリアライズ
     * 
     * @param data 入力データ
     * @param offset オフセット
     * @return std::size_t 変換後のサイズ
     */
	auto fromBinary(const std::vector<std::uint8_t>& data, std::size_t offset = 0) -> std::size_t {
		return fromBinary(data.data(), offset);
	}
};

/**
 * @brief バイナリ変換
 *
 */
struct BinaryConverter {

    /**
     * @brief バイナリサイズを取得
     * 
     * @tparam T 変換対象の型
     * @param input 変換対象の値
     * @return std::size_t サイズ
     */
	template <class Input>
	static auto size(const Input& input) -> std::size_t {
		if constexpr (string_type<Input>) {
			return sizeof(typename Input::value_type) * input.size();
		} else if constexpr (std::is_arithmetic_v<Input> || std::is_enum_v<Input>) {
			return sizeof(Input);
		} else if constexpr (not_string_sequence_container_type<Input>) {
			return sizeof(typename Input::value_type) * input.size();
		} else if constexpr (std::is_base_of_v<BinaryConverterInterface, Input> || HasToBinary<Input>) {
			return input.size();
		} else {
			throw ConvertException("Not supported type", ConvertException::NotSupportedTypeError);
			return 0;
		}
	}

    /**
     * @brief バイナリにシリアライズ
     * 
     * @tparam Input 変換対象の型
     * @param input 変換対象の値
     * @param output 出力データ
     * @param offset オフセット
     * @return std::size_t シリアライズ後のサイズ
     */
	template <class Input>
	static auto toBinary(const Input& input, std::uint8_t* output, std::size_t offset = 0) -> std::size_t {
		if constexpr (std::is_arithmetic_v<Input> || std::is_enum_v<Input>) {
			*reinterpret_cast<Input*>(output + offset) = to_big_endian(input);
			return sizeof(Input);
		} else if constexpr (sequence_container_type<Input>) {
			for (size_t i = 0; i < input.size(); i++) {
				*reinterpret_cast<typename Input::value_type*>(output + offset + i * sizeof(typename Input::value_type)) =
				  to_big_endian(input[i]);
			}
			return sizeof(typename Input::value_type) * input.size();
		} else if constexpr (std::is_base_of_v<BinaryConverterInterface, Input> || HasToBinary<Input>) {
			return input.toBinary(output, offset);
		} else {
			throw ConvertException("Not supported type", ConvertException::NotSupportedTypeError);
			return 0;
		}
	}

    /**
     * @brief バイナリにシリアライズ
     * 
     * @tparam Input 変換対象の型
     * @param input 変換対象の値
     * @param output 出力データ
     * @param offset オフセット
     * @return std::uint8_t* シリアライズ後のデータ
     */
	template <class Input>
	static auto toBinary(const Input& input, std::vector<std::uint8_t>& output, std::size_t offset = 0) -> std::uint8_t* {
		if constexpr (std::is_base_of_v<BinaryConverterInterface, Input> || HasToBinary<Input>) {
			return input.toBinary(output, offset);
		} else if constexpr (sequence_container_type<Input>) {
			if (output.size() < input.size() * sizeof(typename Input::value_type) + offset) {
				output.resize(input.size() * sizeof(typename Input::value_type) + offset);
			}
			return toBinary(input, output.data(), offset);
		} else {
			if (output.size() < sizeof(input) + offset) {
				output.resize(input.size() + offset);
			}
			return toBinary(input, output.data(), offset);
		}
	}

    /**
     * @brief バイナリからデシリアライズ
     * 
     * @tparam Output 出力型
     * @param input 入力データ
     * @param output 出力データ
     * @param offset オフセット
     * @return std::size_t デシリアライズ後のサイズ
     */
	template <class Output>
	static auto fromBinary(const std::uint8_t* input, Output& output, std::size_t offset = 0) -> std::size_t {
		if constexpr (std::is_arithmetic_v<Output> || std::is_enum_v<Output>) {
			output = to_big_endian(*reinterpret_cast<const Output*>(input + offset));
			return sizeof(Output);
		} else if constexpr (sequence_container_type<Output>) { // 先にメモリを確保しておくこと
			for (size_t i = 0; i < output.size(); i++) {
				output[i] = to_big_endian(
				  *reinterpret_cast<const typename Output::value_type*>(input + offset + i * sizeof(typename Output::value_type)));
			}
			return sizeof(typename Output::value_type) * output.size();
		} else if constexpr (std::is_base_of_v<BinaryConverterInterface, Output> || HasFromBinary<Output>) {
			return output.fromBinary(input, offset);
		} else {
			throw ConvertException("Not supported type", ConvertException::NotSupportedTypeError);
			return 0;
		}
	}

    /**
     * @brief バイナリからデシリアライズ
     * 
     * @tparam Output 出力型
     * @param input 入力データ
     * @param output 出力データ
     * @param offset オフセット
     * @return std::size_t デシリアライズ後のサイズ
     */
	template <class Output>
	static auto fromBinary(const std::vector<std::uint8_t>& input, Output& output, std::size_t offset = 0) -> std::size_t {
		if constexpr (std::is_base_of_v<BinaryConverterInterface, Output> || HasFromBinary<Output>) {
			return output.fromBinary(input, offset);
		} else if constexpr (sequence_container_type<Output>) {
			if (input.size() < output.size() * sizeof(typename Output::value_type) + offset) {
				throw ConvertException("Input data size is too small", ConvertException::RequestedDataSizeError);
			}
			return fromBinary(input.data(), output, offset);
		} else {
			if (input.size() < sizeof(output) + offset) {
				throw ConvertException("Input data size is too small", ConvertException::RequestedDataSizeError);
			}
			return fromBinary(input.data(), output, offset);
		}
	}
};

/**
 * @brief JSON変換インターフェース
 *
 */
struct JsonConverterInterface {
	/**
     * @brief JSONのシリアライズ
     * 
     * @return std::string JSON文字列
     */
    virtual auto toJsonString() const -> std::string = 0;
	
    /**
     * @brief JSONのデシリアライズ
     */
    virtual auto fromJsonString(const std::string& json) -> void = 0;
};

DATACONV_NAMESPACE_END

// 以降マクロ魔術
// clang-format off

/**
 * @brief デフォルトデリミタ 
 * 
 */
#define DATACONV_DEFAULT_DELIMITER DATACONV_NAMESPACE_BASE_TAG::SsvFormatPolicy::delimiter

/**
 * @brief 生成する関数名 (to_string)
 * 
 */
#define DATACONV_CODE_GEN_RESULT_TO_STRING DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(to_string)

/**
 * @brief to_string() オペレータージェネレーター
 */
#define DATACONV_CODE_GEN_OPERATOR_TO_STRING(value) \
	DATACONV_CODE_GEN_ARG_STR_T += \
        DATACONV_NAMESPACE_BASE_TAG::StringConverter::toString(DATACONV_CODE_GEN_ARG_OBJ_T.value, delimiter, true); \

/**
 * @brief to_string() ファンクションジェネレーター
 */
#define DATACONV_DEFINE_TO_STRING(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
	friend auto DATACONV_CODE_GEN_RESULT_TO_STRING(std::string& DATACONV_CODE_GEN_ARG_STR_T, \
                         		const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T, \
				const std::string& delimiter = DATACONV_DEFAULT_DELIMITER, \
						bool inc_end = false) \
	->void { \
		DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_TO_STRING, __VA_ARGS__)); \
		if (!inc_end) \
			DATACONV_CODE_GEN_ARG_STR_T.erase(DATACONV_CODE_GEN_ARG_STR_T.size() - delimiter.size(), delimiter.size()); \
	} \
	\
	auto toString(const std::string& delimiter = DATACONV_DEFAULT_DELIMITER, bool inc_end = false) const \
	-> std::string override {	\
		std::string str; \
		str.reserve(256); \
		DATACONV_CODE_GEN_RESULT_TO_STRING(str, *this, delimiter, inc_end); \
		return str; \
	} \
	\
	friend auto operator<<(std::ostream& os, \
						   DATACONV_CODE_GEN_TEMPLATE_TYPE& obj)	\
	-> std::ostream& { \
    	os << obj.toString(); \
    	return os; \
	}

	/**
	 * @brief 生成する関数名 (make_header)
	 * 
	 */
	#define DATACONV_CODE_GEN_RESULT_MAKE_HEADER DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(make_header)

	/**
	 * @brief make_header() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_MAKE_HEADER(value) \
		DATACONV_CODE_GEN_ARG_STR_T += \
        	DATACONV_NAMESPACE_BASE_TAG::StringConverter::makeHeader(#value, DATACONV_CODE_GEN_ARG_OBJ_T.value, delimiter, true);
	
	#define DATACONV_DEFINE_MAKE_HEADER(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		friend auto DATACONV_CODE_GEN_RESULT_MAKE_HEADER(const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T, \
																	   const std::string& delimiter = DATACONV_DEFAULT_DELIMITER, \
																	   bool inc_end = false) \
		-> std::string { \
			std::string DATACONV_CODE_GEN_ARG_STR_T; \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_MAKE_HEADER, __VA_ARGS__)); \
			if (!inc_end) \
				DATACONV_CODE_GEN_ARG_STR_T.pop_back(); \
			return DATACONV_CODE_GEN_ARG_STR_T; \
		} \
		\
		auto makeHeader(const std::string& delimiter = DATACONV_DEFAULT_DELIMITER, bool inc_end = false)	\
		const -> std::string override {	\
			return DATACONV_CODE_GEN_RESULT_MAKE_HEADER(*this, delimiter, inc_end); \
		}																																																																						\

	/**
	 * @brief 生成する関数名 (size())
	 * 
	 **/
	#define DATACONV_CODE_GEN_RESULT_SIZE DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(size)

	/**
	 * @brief size() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_SIZE(value) \
		DATACONV_CODE_GEN_ARG_PTR_T += DATACONV_NAMESPACE_BASE_TAG::BinaryConverter::size(DATACONV_CODE_GEN_ARG_OBJ_T.value);

	#define DATACONV_DEFINE_SIZE(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		friend auto DATACONV_CODE_GEN_RESULT_SIZE(const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T)	\
		-> std::size_t { \
			std::size_t DATACONV_CODE_GEN_ARG_PTR_T = 0; \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_SIZE, __VA_ARGS__)); \
			return DATACONV_CODE_GEN_ARG_PTR_T; \
		} \
		\
		auto size() const -> std::size_t override {	\
			return DATACONV_CODE_GEN_RESULT_SIZE(*this);	\
		}
	
	/**
	 * @brief 生成する関数名 (to_binary)
	 * 
	 */
	#define DATACONV_CODE_GEN_RESULT_TO_BINARY DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(to_binary)

	/**
	 * @brief to_binary() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_TO_BINARY(value)	\
		DATACONV_CODE_GEN_ARG_PTR_T += \
			DATACONV_NAMESPACE_BASE_TAG::BinaryConverter::toBinary(DATACONV_CODE_GEN_ARG_OBJ_T.value, \
																					   DATACONV_CODE_GEN_ARG_OPT_T, \
																					   DATACONV_CODE_GEN_ARG_PTR_T);


	#define DATACONV_DEFINE_TO_BINARY(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		friend auto DATACONV_CODE_GEN_RESULT_TO_BINARY(const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T, \
																  std::uint8_t* DATACONV_CODE_GEN_ARG_OPT_T, \
							  									  std::size_t DATACONV_CODE_GEN_ARG_OFS_T = 0) \
		-> std::size_t { \
			std::size_t DATACONV_CODE_GEN_ARG_PTR_T = DATACONV_CODE_GEN_ARG_OFS_T; \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_TO_BINARY, __VA_ARGS__)); \
			return DATACONV_CODE_GEN_ARG_PTR_T - DATACONV_CODE_GEN_ARG_OFS_T; \
		} \
		\
		auto toBinary(std::uint8_t* DATACONV_CODE_GEN_ARG_OPT_T, \
					  std::size_t DATACONV_CODE_GEN_ARG_OFS_T = 0) \
		const -> std::size_t override {	\
			return DATACONV_CODE_GEN_RESULT_TO_BINARY(*this, \
																 DATACONV_CODE_GEN_ARG_OPT_T, \
																 DATACONV_CODE_GEN_ARG_OFS_T); \
		} \
		\
		friend auto operator>>(const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T,\
							   std::vector<std::uint8_t>& DATACONV_CODE_GEN_ARG_OPT_T) \
		-> const DATACONV_CODE_GEN_TEMPLATE_TYPE& { \
			DATACONV_CODE_GEN_ARG_OBJ_T.toBinary(DATACONV_CODE_GEN_ARG_OPT_T); \
			return DATACONV_CODE_GEN_ARG_OBJ_T; \
		} \
		\
		using DATACONV_NAMESPACE_BASE_TAG::BinaryConverterInterface::toBinary;						
	
	/**
	 * @brief 生成する関数名 (from_binary)
	 * 
	 */
	#define DATACONV_CODE_GEN_RESULT_FROM_BINARY DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(from_binary)

	/**
	 * @brief from_binary() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_FROM_BINARY(value) \
		DATACONV_CODE_GEN_ARG_PTR_T += \
			DATACONV_NAMESPACE_BASE_TAG::BinaryConverter::fromBinary(DATACONV_CODE_GEN_ARG_IPT_T, \
																								   DATACONV_CODE_GEN_ARG_OBJ_T.value, \
																								   DATACONV_CODE_GEN_ARG_PTR_T);

	#define DATACONV_DEFINE_FROM_BINARY(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...)	\
		friend auto DATACONV_CODE_GEN_RESULT_FROM_BINARY(const std::uint8_t* DATACONV_CODE_GEN_ARG_IPT_T, \
																	DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T, \
							  										std::size_t DATACONV_CODE_GEN_ARG_OFS_T = 0) \
		-> std::size_t { \
			std::size_t DATACONV_CODE_GEN_ARG_PTR_T = DATACONV_CODE_GEN_ARG_OFS_T; \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_FROM_BINARY, __VA_ARGS__)); \
			return DATACONV_CODE_GEN_ARG_PTR_T - DATACONV_CODE_GEN_ARG_OFS_T;	\
		} \
		\
		auto fromBinary(const std::uint8_t* DATACONV_CODE_GEN_ARG_IPT_T,	\
					    std::size_t DATACONV_CODE_GEN_ARG_OFS_T = 0) \
						-> std::size_t override { \
			return DATACONV_CODE_GEN_RESULT_FROM_BINARY(DATACONV_CODE_GEN_ARG_IPT_T, \
																   *this, \
																   DATACONV_CODE_GEN_ARG_OFS_T); \
		} \
		\
		friend auto operator<<(DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T, \
							   const std::vector<std::uint8_t>& DATACONV_CODE_GEN_ARG_IPT_T) \
		-> DATACONV_CODE_GEN_TEMPLATE_TYPE& { \
			DATACONV_CODE_GEN_ARG_OBJ_T.fromBinary(DATACONV_CODE_GEN_ARG_IPT_T); \
			return DATACONV_CODE_GEN_ARG_OBJ_T; \
		} \
		\
		using DATACONV_NAMESPACE_BASE_TAG::BinaryConverterInterface::fromBinary;

	/**
	 * @brief 生成する関数名 (to_json)
	 * @remarks nlohmannに渡す為，名前を変更している
	 */

	/**
	 * @brief to_josn() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_TO_JSON(value) \
		DATACONV_CODE_GEN_ARG_OPT_T[#value] = DATACONV_CODE_GEN_ARG_OBJ_T.value;
	
	#define DATACONV_DEFINE_TO_JSON(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		template <class DefaultJsonType> \
		friend auto to_json(DefaultJsonType& DATACONV_CODE_GEN_ARG_OPT_T, \
							const DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T) \
		-> void { \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_TO_JSON, __VA_ARGS__)); \
		} \
		auto toJsonString() const -> std::string override { \
			return DATACONV_NAMESPACE_BASE_TAG::ordered_json(*this).dump(4); \
		}
	
	/**
	 * @brief 生成する関数名 (from_json)
	 * @remarks nlohmannに渡す為，名前を変更している
	 */

	/**
	 * @brief from_josn() オペレータージェネレーター
	 */
	#define DATACONV_CODE_GEN_OPERATOR_FROM_JSON(v) \
		DATACONV_CODE_GEN_ARG_OBJ_T.v = DATACONV_CODE_GEN_ARG_IPT_T.value(#v, DATACONV_CODE_GEN_INITIALIZED_OBJ_T.v);

	#define DATACONV_DEFINE_FROM_JSON(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		template <class DefaultJsonType> \
		friend auto from_json(const DefaultJsonType& DATACONV_CODE_GEN_ARG_IPT_T, \
							  DATACONV_CODE_GEN_TEMPLATE_TYPE& DATACONV_CODE_GEN_ARG_OBJ_T) \
		-> void { \
			auto DATACONV_CODE_GEN_INITIALIZED_OBJ_T = DATACONV_CODE_GEN_TEMPLATE_TYPE(); \
			DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_PASTE(DATACONV_CODE_GEN_OPERATOR_FROM_JSON, __VA_ARGS__)); \
		} \
		auto fromJsonString(const std::string& json) -> void override { \
			from_json(DATACONV_NAMESPACE_BASE_TAG::json::parse(json), *this); \
		}
	
	#define DATACONV_DEFINE_JSON_SERIALIZE_ENUM(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) NLOHMANN_JSON_SERIALIZE_ENUM(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)


    /**
     * @brief 文字列変換コード生成
     * 
     */
	#define  DATACONV_DEFINE_REQUIRED_STRING_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		DATACONV_DEFINE_TO_STRING(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_MAKE_HEADER(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)
		// DATACONV_DEFINE_FROM_STRING(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)																			

    /**
     * @brief バイナリ変換コード生成
     * 
     */
	#define  DATACONV_DEFINE_REQUIRED_BINARY_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		DATACONV_DEFINE_SIZE(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_TO_BINARY(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_FROM_BINARY(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)

    /**
     * @brief JSON変換コード生成
     * 
     */
	#define DATACONV_DEFINE_REQUIRED_JSON_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...) \
		DATACONV_DEFINE_TO_JSON(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_FROM_JSON(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)

	/**
     * @brief マルチ変換コード生成
     * 
     */
    #define DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, ...)	\
		DATACONV_DEFINE_REQUIRED_STRING_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_REQUIRED_BINARY_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__) \
		DATACONV_DEFINE_REQUIRED_JSON_CONVERTER(DATACONV_CODE_GEN_TEMPLATE_TYPE, __VA_ARGS__)

    /**
     * @brief 文字列変換機能継承のショートハンド
     * 
     */
	#define DATACONV_WITH_STRING_CONVERTER \
		public DATACONV_NAMESPACE_BASE_TAG::StringConverterInterface

    /**
     * @brief バイナリ変換機能継承のショートハンド
     * 
     */
	#define DATACONV_WITH_BINARY_CONVERTER \
		public DATACONV_NAMESPACE_BASE_TAG::BinaryConverterInterface

    /**
     * @brief JSON変換機能継承のショートハンド
     * 
     */
	#define DATACONV_WITH_JSON_CONVERTER \
		public DATACONV_NAMESPACE_BASE_TAG::JsonConverterInterface

    /**
     * @brief マルチ変換機能継承のショートハンド
     * 
     */
	#define DATACONV_WITH_MULTI_CONVERTER \
		DATACONV_WITH_STRING_CONVERTER, \
		DATACONV_WITH_BINARY_CONVERTER, \
		DATACONV_WITH_JSON_CONVERTER
// clang-format on