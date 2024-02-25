/**
 * @file Macro.hpp
 * @author fugu133
 * @brief
 * @version 0.1
 * @date 2024-02-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

// clang-format off
#define DATACONV_VERSION_MAJOR 1
#define DATACONV_VERSION_MINOR 0
#define DATACONV_VERSION_PATCH 0

#define DATACONV_TO_STRING_EX(x) #x
#define DATACONV_TO_STRING(x) DATACONV_TO_STRING_EX(x)

#define DATACONV_VERSION_CONCAT_EX(major, minor, patch) v ## major.minor.patch
#define DATACONV_VERSION_CONCAT(major, minor, patch) DATACONV_VERSION_CONCAT_EX(major, minor, patch)

#define DATACONV_VERSION_EX \
	DATACONV_VERSION_CONCAT(DATACONV_VERSION_MAJOR, \
				      DATACONV_VERSION_MINOR, \
			              DATACONV_VERSION_PATCH)
#define DATACONV_VERSION DATACONV_VERSION_EX
#define DATACONV_VERSION_STR_EX DATACONV_TO_STRING(DATACONV_VERSION)
#define DATACONV_VERSION_STR DATACONV_VERSION_STR_EX

#define DATACONV_NAMESPACE_VERSION_TAG_CONCAT_EX(major, minor, patch) v ## major ## _ ## minor ## _ ## patch
#define DATACONV_NAMESPACE_VERSION_TAG_CONCAT(major, minor, patch) DATACONV_NAMESPACE_VERSION_TAG_CONCAT_EX(major, minor, patch)
#define DATACONV_NAMESPACE_VERSION_TAG_EX \
	DATACONV_NAMESPACE_VERSION_TAG_CONCAT(DATACONV_VERSION_MAJOR, \
						    DATACONV_VERSION_MINOR, \
					            DATACONV_VERSION_PATCH)
#define DATACONV_NAMESPACE_BASE_TAG dataconv
#define DATACONV_NAMESPACE_VERSION_TAG DATACONV_NAMESPACE_VERSION_TAG_EX
#define DATACONV_NAMESPACE_BEGIN \
	namespace DATACONV_NAMESPACE_BASE_TAG {                   \
		inline namespace DATACONV_NAMESPACE_VERSION_TAG {
#define DATACONV_NAMESPACE_END \
	}                                               \
}

#define DATACONV_REQUEST_VERSION_CHECK(major, minor, patch) \
	(DATACONV_VERSION_MAJOR >= major && DATACONV_VERSION_MINOR >= minor && DATACONV_VERSION_PATCH >= patch)

#define DATACONV_REQUEST_VERSION_ASSERTION_MSG_STR(major, minor, patch) "DATACONV-Lib must be has version higher than " DATACONV_TO_STRING(DATACONV_VERSION_CONCAT(major, minor, patch))

#ifndef DATACONV_NO_ASSERTION
#define DATACONV_ASSRET_CONVERTER_REQUEST_VERSION(major, minor, patch) \
	static_assert(DATACONV_REQUEST_VERSION_CHECK(major, minor, patch), DATACONV_REQUEST_VERSION_ASSERTION_MSG_STR(major, minor, patch))
#else
	TELEMETRY_ASSRET_CONVERTER_REQUEST_VERSION(major, minor, patch)
#endif

#define DATACONV_CODE_GEN_CONCAT_EX(tag, type) tag ## _ ## type
#define DATACONV_CODE_GEN_CONCAT(tag, type) DATACONV_CODE_GEN_CONCAT_EX(tag, type)
#define DATACONV_CODE_GEN_TAG dataconv_code_gen
#define DATACONV_CODE_GEN_RESULT_FUNCTION_NAME(x) DATACONV_CODE_GEN_CONCAT(DATACONV_CODE_GEN_TAG, x)
#define DATACONV_CODE_GEN_ARG_STR_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, str_t)
#define DATACONV_CODE_GEN_ARG_OBJ_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, obj_t)
#define DATACONV_CODE_GEN_ARG_PTR_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, ptr_t)
#define DATACONV_CODE_GEN_ARG_OFS_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, ofs_t)
#define DATACONV_CODE_GEN_ARG_IPT_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, ipt_t)
#define DATACONV_CODE_GEN_ARG_OPT_T DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, opt_t)
#define DATACONV_CODE_GEN_TEMPLATE_TYPE Type
#define DATACONV_CODE_GEN_TARGET_OBJ_NAME DATACONV_CODE_GEN_CONCAT(DATACONV_NAMESPACE_BASE_TAG, obj_name)
#define DATACONV_CODE_GEN_ARG_EXPAND( x ) x
#define DATACONV_CODE_GEN_ARG_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define DATACONV_CODE_GEN_ARG_PASTE(...) DATACONV_CODE_GEN_ARG_EXPAND(DATACONV_CODE_GEN_ARG_GET_MACRO(__VA_ARGS__, \
        DATACONV_CODE_GEN_ARG_PASTE64, \
        DATACONV_CODE_GEN_ARG_PASTE63, \
        DATACONV_CODE_GEN_ARG_PASTE62, \
        DATACONV_CODE_GEN_ARG_PASTE61, \
        DATACONV_CODE_GEN_ARG_PASTE60, \
        DATACONV_CODE_GEN_ARG_PASTE59, \
        DATACONV_CODE_GEN_ARG_PASTE58, \
        DATACONV_CODE_GEN_ARG_PASTE57, \
        DATACONV_CODE_GEN_ARG_PASTE56, \
        DATACONV_CODE_GEN_ARG_PASTE55, \
        DATACONV_CODE_GEN_ARG_PASTE54, \
        DATACONV_CODE_GEN_ARG_PASTE53, \
        DATACONV_CODE_GEN_ARG_PASTE52, \
        DATACONV_CODE_GEN_ARG_PASTE51, \
        DATACONV_CODE_GEN_ARG_PASTE50, \
        DATACONV_CODE_GEN_ARG_PASTE49, \
        DATACONV_CODE_GEN_ARG_PASTE48, \
        DATACONV_CODE_GEN_ARG_PASTE47, \
        DATACONV_CODE_GEN_ARG_PASTE46, \
        DATACONV_CODE_GEN_ARG_PASTE45, \
        DATACONV_CODE_GEN_ARG_PASTE44, \
        DATACONV_CODE_GEN_ARG_PASTE43, \
        DATACONV_CODE_GEN_ARG_PASTE42, \
        DATACONV_CODE_GEN_ARG_PASTE41, \
        DATACONV_CODE_GEN_ARG_PASTE40, \
        DATACONV_CODE_GEN_ARG_PASTE39, \
        DATACONV_CODE_GEN_ARG_PASTE38, \
        DATACONV_CODE_GEN_ARG_PASTE37, \
        DATACONV_CODE_GEN_ARG_PASTE36, \
        DATACONV_CODE_GEN_ARG_PASTE35, \
        DATACONV_CODE_GEN_ARG_PASTE34, \
        DATACONV_CODE_GEN_ARG_PASTE33, \
        DATACONV_CODE_GEN_ARG_PASTE32, \
        DATACONV_CODE_GEN_ARG_PASTE31, \
        DATACONV_CODE_GEN_ARG_PASTE30, \
        DATACONV_CODE_GEN_ARG_PASTE29, \
        DATACONV_CODE_GEN_ARG_PASTE28, \
        DATACONV_CODE_GEN_ARG_PASTE27, \
        DATACONV_CODE_GEN_ARG_PASTE26, \
        DATACONV_CODE_GEN_ARG_PASTE25, \
        DATACONV_CODE_GEN_ARG_PASTE24, \
        DATACONV_CODE_GEN_ARG_PASTE23, \
        DATACONV_CODE_GEN_ARG_PASTE22, \
        DATACONV_CODE_GEN_ARG_PASTE21, \
        DATACONV_CODE_GEN_ARG_PASTE20, \
        DATACONV_CODE_GEN_ARG_PASTE19, \
        DATACONV_CODE_GEN_ARG_PASTE18, \
        DATACONV_CODE_GEN_ARG_PASTE17, \
        DATACONV_CODE_GEN_ARG_PASTE16, \
        DATACONV_CODE_GEN_ARG_PASTE15, \
        DATACONV_CODE_GEN_ARG_PASTE14, \
        DATACONV_CODE_GEN_ARG_PASTE13, \
        DATACONV_CODE_GEN_ARG_PASTE12, \
        DATACONV_CODE_GEN_ARG_PASTE11, \
        DATACONV_CODE_GEN_ARG_PASTE10, \
        DATACONV_CODE_GEN_ARG_PASTE9, \
        DATACONV_CODE_GEN_ARG_PASTE8, \
        DATACONV_CODE_GEN_ARG_PASTE7, \
        DATACONV_CODE_GEN_ARG_PASTE6, \
        DATACONV_CODE_GEN_ARG_PASTE5, \
        DATACONV_CODE_GEN_ARG_PASTE4, \
        DATACONV_CODE_GEN_ARG_PASTE3, \
        DATACONV_CODE_GEN_ARG_PASTE2, \
        DATACONV_CODE_GEN_ARG_PASTE1)(__VA_ARGS__))
#define DATACONV_CODE_GEN_ARG_PASTE1
#define DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) operator_function(v1)
#define DATACONV_CODE_GEN_ARG_PASTE3(operator_function, v1, v2) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v2)
#define DATACONV_CODE_GEN_ARG_PASTE4(operator_function, v1, v2, v3) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE3(operator_function, v2, v3)
#define DATACONV_CODE_GEN_ARG_PASTE5(operator_function, v1, v2, v3, v4) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE4(operator_function, v2, v3, v4)
#define DATACONV_CODE_GEN_ARG_PASTE6(operator_function, v1, v2, v3, v4, v5) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE5(operator_function, v2, v3, v4, v5)
#define DATACONV_CODE_GEN_ARG_PASTE7(operator_function, v1, v2, v3, v4, v5, v6) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE6(operator_function, v2, v3, v4, v5, v6)
#define DATACONV_CODE_GEN_ARG_PASTE8(operator_function, v1, v2, v3, v4, v5, v6, v7) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE7(operator_function, v2, v3, v4, v5, v6, v7)
#define DATACONV_CODE_GEN_ARG_PASTE9(operator_function, v1, v2, v3, v4, v5, v6, v7, v8) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE8(operator_function, v2, v3, v4, v5, v6, v7, v8)
#define DATACONV_CODE_GEN_ARG_PASTE10(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE9(operator_function, v2, v3, v4, v5, v6, v7, v8, v9)
#define DATACONV_CODE_GEN_ARG_PASTE11(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE10(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define DATACONV_CODE_GEN_ARG_PASTE12(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE11(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define DATACONV_CODE_GEN_ARG_PASTE13(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE12(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define DATACONV_CODE_GEN_ARG_PASTE14(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE13(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define DATACONV_CODE_GEN_ARG_PASTE15(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE14(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define DATACONV_CODE_GEN_ARG_PASTE16(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE15(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define DATACONV_CODE_GEN_ARG_PASTE17(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE16(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define DATACONV_CODE_GEN_ARG_PASTE18(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE17(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define DATACONV_CODE_GEN_ARG_PASTE19(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE18(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define DATACONV_CODE_GEN_ARG_PASTE20(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE19(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define DATACONV_CODE_GEN_ARG_PASTE21(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE20(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define DATACONV_CODE_GEN_ARG_PASTE22(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE21(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define DATACONV_CODE_GEN_ARG_PASTE23(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE22(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define DATACONV_CODE_GEN_ARG_PASTE24(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE23(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define DATACONV_CODE_GEN_ARG_PASTE25(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE24(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define DATACONV_CODE_GEN_ARG_PASTE26(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE25(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define DATACONV_CODE_GEN_ARG_PASTE27(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE26(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define DATACONV_CODE_GEN_ARG_PASTE28(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE27(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define DATACONV_CODE_GEN_ARG_PASTE29(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE28(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define DATACONV_CODE_GEN_ARG_PASTE30(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE29(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define DATACONV_CODE_GEN_ARG_PASTE31(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE30(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define DATACONV_CODE_GEN_ARG_PASTE32(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE31(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define DATACONV_CODE_GEN_ARG_PASTE33(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE32(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define DATACONV_CODE_GEN_ARG_PASTE34(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE33(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define DATACONV_CODE_GEN_ARG_PASTE35(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE34(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define DATACONV_CODE_GEN_ARG_PASTE36(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE35(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define DATACONV_CODE_GEN_ARG_PASTE37(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE36(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define DATACONV_CODE_GEN_ARG_PASTE38(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE37(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define DATACONV_CODE_GEN_ARG_PASTE39(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE38(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define DATACONV_CODE_GEN_ARG_PASTE40(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE39(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define DATACONV_CODE_GEN_ARG_PASTE41(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE40(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define DATACONV_CODE_GEN_ARG_PASTE42(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE41(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define DATACONV_CODE_GEN_ARG_PASTE43(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE42(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define DATACONV_CODE_GEN_ARG_PASTE44(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE43(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define DATACONV_CODE_GEN_ARG_PASTE45(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE44(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define DATACONV_CODE_GEN_ARG_PASTE46(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE45(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define DATACONV_CODE_GEN_ARG_PASTE47(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE46(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define DATACONV_CODE_GEN_ARG_PASTE48(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE47(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define DATACONV_CODE_GEN_ARG_PASTE49(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE48(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define DATACONV_CODE_GEN_ARG_PASTE50(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE49(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define DATACONV_CODE_GEN_ARG_PASTE51(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE50(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define DATACONV_CODE_GEN_ARG_PASTE52(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE51(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define DATACONV_CODE_GEN_ARG_PASTE53(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE52(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define DATACONV_CODE_GEN_ARG_PASTE54(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE53(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define DATACONV_CODE_GEN_ARG_PASTE55(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE54(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define DATACONV_CODE_GEN_ARG_PASTE56(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE55(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define DATACONV_CODE_GEN_ARG_PASTE57(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE56(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define DATACONV_CODE_GEN_ARG_PASTE58(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE57(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define DATACONV_CODE_GEN_ARG_PASTE59(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE58(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define DATACONV_CODE_GEN_ARG_PASTE60(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE59(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define DATACONV_CODE_GEN_ARG_PASTE61(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE60(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define DATACONV_CODE_GEN_ARG_PASTE62(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE61(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define DATACONV_CODE_GEN_ARG_PASTE63(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE62(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define DATACONV_CODE_GEN_ARG_PASTE64(operator_function, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) DATACONV_CODE_GEN_ARG_PASTE2(operator_function, v1) DATACONV_CODE_GEN_ARG_PASTE63(operator_function, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

// clang-format on