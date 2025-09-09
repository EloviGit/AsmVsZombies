#ifndef __AVZ_MULTI_PLATFORM_H__
#define __AVZ_MULTI_PLATFORM_H__

// Tool macros.
#define __AJOIN_IMPL_(x, y)             x##_##y
#define __AJOIN(x, y)                   __AJOIN_IMPL_(x, y)
#define __ASTR_IMPL_(x)                 #x
#define __ASTR(x)                       __ASTR_IMPL_(x)
// Given x, check if __x expands to empty.
#define __AIS_VALID_IMPL2_(_1, _2, ...)     _2
#define __AIS_VALID_IMPL1_(...)             __AIS_VALID_IMPL2_(__VA_ARGS__ __VA_OPT__(,) false, true)
#define __AIS_VALID(x)                      __AIS_VALID_IMPL1_(x)
// Generate new filename: (id, header) -> id/id_header
#define __ANEW_FILENAME(id, header)                 __ASTR(id/__AJOIN(id, header))

// Strong platform dependent: this feature is not supported by all platforms.
// Weak platform dependent: this feature is supported by all platforms, but implemented in different ways.
// Platform independent: this feature is supported in all platforms and works the same.

// compile-time option: -DPLATFORM=ORIGINAL, -DPLATFORM=PVZ_EMULATOR

// To add a new platform:
// 1. In CMake compile definition: use -DPLATFORM=NEW_P.
// 2. Define __NEW_P_str(files located in new_p/new_p_avz_XX) and define __NEW_P to empty.
// 3. Define HEADER_NEW_P(XX) to specify the path of new platform files.
// 4. Implement your code in inc/new_platform/ and src/new_platform/
// 5. All files need to include avz_multi_platform.h
// 6. To include inc/new_platform/newplatform_avz_XX.h, use HEADER_NEW_P(avz_XX.h)

//////////////////////////////////////////////////////////////////////////////////////////////////
// Define all supported platforms below. Do not modify outside this block.                      //
//////////////////////////////////////////////////////////////////////////////////////////////////
#define __ORIGINAL_str                      original                                            //
#define __ORIGINAL                                                                              //
#define HEADER_ORIGINAL(header)             __ANEW_FILENAME(__ORIGINAL_str, header)             //
                                                                                                //
#define __PVZ_EMULATOR_str                  pvz_emulator                                        //
#define __PVZ_EMULATOR                                                                          //
#define HEADER_PVZ_EMULATOR(header)         __ANEW_FILENAME(__PVZ_EMULATOR_str, header)         //
//////////////////////////////////////////////////////////////////////////////////////////////////
// Define all supported platforms above. Do not modify outside this block.                      //
//////////////////////////////////////////////////////////////////////////////////////////////////

// If no platform macro is specified, default to ORIGINAL
#ifndef PLATFORM
#define PLATFORM                            ORIGINAL
#endif

// Check if PLATFORM is a defined platform above:
// by checking if __PLATFORM expands to empty.
#if !__AIS_VALID(__AJOIN(_, PLATFORM))
#error "Unrecognized PLATFORM!"
#endif

#define __PLATFORM_str                      __AJOIN(_, __AJOIN(PLATFORM, str))
#define HEADER_PLATFORM(header)             __ANEW_FILENAME(__PLATFORM_str, header)
#define HEADER_SHARED(header)               __ANEW_FILENAME(shared, header)

// Concatenate type name and platform identifier
#define __ATypeP(Name, Platform)            __AJOIN(Name, Platform)

#endif