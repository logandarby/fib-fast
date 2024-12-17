#pragma once

#include "base.h"
#include <filesystem>

#ifdef ENABLE_ASSERTS

    // Alteratively we could use the same "default" message for both "WITH_MSG"
    // and "NO_MSG" and provide support for custom formatting by concatenating
    // the formatting string instead of having the format inside the default
    // message
    #define _INTERNAL_ASSERT_IMPL(check, msg, ...) { if(!(check)) { LOG_ERR(msg, __VA_ARGS__); __debugbreak(); } }
    #define _INTERNAL_ASSERT_WITH_MSG(check, ...) _INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", __VA_ARGS__)
    #define _INTERNAL_ASSERT_NO_MSG(check) _INTERNAL_ASSERT_IMPL(check, "Assertion '{0}' failed at {1}:{2}", _STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define _INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define _INTERNAL_ASSERT_GET_MACRO(...) _INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, _INTERNAL_ASSERT_WITH_MSG, _INTERNAL_ASSERT_NO_MSG)

    // Currently accepts at least the condition and one additional parameter
    // (the message) being optional
    #define ASSERT(...)  _INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__)
#else
    #define ASSERT(...)
#endif