// Macro Definitions

#ifdef _DEBUG
    #define BUILD_TYPE "Debug"
    #define ENABLE_ASSERTS
#else
    #define BUILD_TYPE "Release"
#endif

#define _STRINGIFY_MACRO(x) #x