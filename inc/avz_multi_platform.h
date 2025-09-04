#ifndef __AVZ_MULTI_PLATFORM_H__
#define __AVZ_MULTI_PLATFORM_H__

// Strong platform dependent: this feature is not supported by all platforms.
// Weak platform dependent: this feature is supported by all platforms, but implemented in different ways.
// Platform independent: this feature is supported in all platforms and works the same.


// At most one platform macro can be defined
#if defined(PLATFORM_ORIGINAL) + defined(PLATFORM_PVZ_EMULATOR) > 1
#error "Only at most one platform macro can be defined"
#endif

// If no platform macro is specified, default to ORIGINAL
#if defined(PLATFORM_ORIGINAL) + defined(PLATFORM_PVZ_EMULATOR) == 0
#define PLATFORM_ORIGINAL
#endif

// enum class __APlatform {
//     UNSUPPORTED,
//     ORIGINAL,
//     PVZ_EMULATOR,
// };

// enum class __AExportType {
//     UNKNOWN,
//     DLL,
//     EXE,
// };


#define __ORIGINAL_IDENTIFIER original
#define __PVZ_EMULATOR_IDENTIFIER pvz_emulator

// compile-time option:
// -DPLATFORM_ORIGINAL, -DPLATFORM_PVZ_EMULATOR
#if defined(PLATFORM_ORIGINAL)
// inline constexpr __APlatform __aPlatform = __APlatform::ORIGINAL;
// inline constexpr __AExportType __aExportType = __AExportType::DLL;
#define __APlatformIdentifier __ORIGINAL_IDENTIFIER
#elif defined(PLATFORM_PVZ_EMULATOR)
// inline constexpr __APlatform __aPlatform = __APlatform::PVZ_EMULATOR;
// inline constexpr __AExportType __aExportType = __AExportType::EXE;
#define __APlatformIdentifier __PVZ_EMULATOR_IDENTIFIER
#else
#error "Unreachable code!"
#endif


#define __AJOIN2(a, b) a##_##b
#define __AJOIN(a, b) __AJOIN2(a, b)
#define __ANEW_FILENAME(header) __AJOIN(__APlatformIdentifier, header)
#define __ASTR2(x) #x
#define __ASTR(x) __ASTR2(x)

#define HEADER_PLATFORM(header) __ASTR(__APlatformIdentifier/__ANEW_FILENAME(header))
#define HEADER_ORIGIN(header) __ASTR(__ORIGINAL_IDENTIFIER/__ANEW_FILENAME(header))
#define HEADER_PVZ_EMULATOR(header) __ASTR(__PVZ_EMULATOR_IDENTIFIER/__ANEW_FILENAME(header))
#define HEADER_ALL(header) HEADER_ORIGIN(header) HEADER_PVZ_EMULATOR(header)

#define NS_PLATFORM(name) __AJOIN(name, __APlatformIdentifier)
#define NS_ORIGIN(name) __AJOIN(name, __ORIGINAL_IDENTIFIER)
#define NS_PVZ_EMULATOR(name) __AJOIN(name, __PVZ_EMULATOR_IDENTIFIER)


#endif