/**
 * @file Exception.hpp
 * @author Kaiji Takeuchi
 * @brief
 * @version 0.1
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <stdexcept>
#include <string>

DATACONV_NAMESPACE_BEGIN
/**
 * @brief 基本例外クラス
 *
 */
class DataConverterBaseException : public std::runtime_error {
  public:
	DataConverterBaseException() = delete;
	DataConverterBaseException(std::string& what_message, int error_code)
	  : runtime_error("[DataConverterException]: " + what_message), error_code(error_code) {}

	int getReturnCode() const { return error_code; }

  private:
	int error_code;
};

class ConvertException : public DataConverterBaseException {
  public:
	ConvertException(std::string&& what_message, int error_code) : DataConverterBaseException(what_message, error_code) {}

	enum { NotSupportedTypeError, RequestedDataSizeError };
};

DATACONV_NAMESPACE_END