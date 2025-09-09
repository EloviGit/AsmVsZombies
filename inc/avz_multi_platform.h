#ifndef __AVZ_MULTI_PLATFORM_H__
#define __AVZ_MULTI_PLATFORM_H__

#define __AJOIN_IMPL_(x, y)             x##_##y
#define __AJOIN(x, y)                   __AJOIN_IMPL_(x, y)
#define __ASTR_IMPL_(x)                 #x
#define __ASTR(x)                       __ASTR_IMPL_(x)
// Generate new filename: (id, header) -> id/id_header
#define __ANEW_FILENAME(id, header)                 __ASTR(id/__AJOIN(id, header))

// Strong platform dependent: this feature is not supported by all platforms.
// Weak platform dependent: this feature is supported by all platforms, but implemented in different ways.
// Platform independent: this feature is supported in all platforms and works the same.

// compile-time option:
// -DPLATFORM_ORIGINAL, -DPLATFORM_PVZ_EMULATOR
// To add a new platform:
// 1. Define a new platform macro, e.g., PLATFORM_NEW_PLATFORM
// 2. Define a new platform identifier macro, e.g., __NEW_PLATFORM_IDENTIFIER new_platform
// 3. Define HEADER_NEW_PLATFORM(header)
// 4. Implement your code in inc/new_platform/ and src/new_platform/
// 5. All files need to include avz_multi_platform.h
// 6. To include inc/new_platform/newplatform_avz_XX.h, use HEADER_NEW_PLATFORM(avz_XX)

#define __ORIGINAL_IDENTIFIER               original
#define HEADER_ORIGINAL(header)             __ANEW_FILENAME(__ORIGINAL_IDENTIFIER, header)

#define __PVZ_EMULATOR_IDENTIFIER           pvz_emulator
#define HEADER_PVZ_EMULATOR(header)         __ANEW_FILENAME(__PVZ_EMULATOR_IDENTIFIER, header)

#if defined(PLATFORM_ORIGINAL) + defined(PLATFORM_PVZ_EMULATOR) > 1
#error "Only at most one platform macro can be defined"
#elif defined(PLATFORM_ORIGINAL) + defined(PLATFORM_PVZ_EMULATOR) == 0
// If no platform macro is specified, default to ORIGINAL
#define PLATFORM_ORIGINAL
#endif

#if defined(PLATFORM_ORIGINAL)
#define __APlatformIdentifier __ORIGINAL_IDENTIFIER
#elif defined(PLATFORM_PVZ_EMULATOR)
#define __APlatformIdentifier __PVZ_EMULATOR_IDENTIFIER
#else
#error "Unreachable code!"
#endif

#define HEADER_PLATFORM(header)             __ANEW_FILENAME(__APlatformIdentifier, header)
#define HEADER_SHARED(header)               __ANEW_FILENAME(shared, header)

#endif