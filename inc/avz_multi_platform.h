#ifndef __AVZ_MULTI_PLATFORM_H__
#define __AVZ_MULTI_PLATFORM_H__

#include <type_traits>

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

#define NS_PLATFORM(name) __AJOIN(name, __APlatformIdentifier)
#define NS_ORIGIN(name) __AJOIN(name, __ORIGINAL_IDENTIFIER)
#define NS_PVZ_EMULATOR(name) __AJOIN(name, __PVZ_EMULATOR_IDENTIFIER)


// 检查类型T是否存在
#define STATIC_ASSERT_TYPE_EXISTS(TYPE) \
    template<typename = void> \
    struct type_exists_##TYPE : std::false_type {}; \
    template<> \
    struct type_exists_##TYPE<decltype(sizeof(TYPE), void())> : std::true_type {};


// 检查类型T是否存在名为MEMBER的public成员
#define STATIC_ASSERT_HAS_PUBLIC_MEMBER(T, MEMBER) \
    template<typename U> \
    class has_member_##MEMBER { \
    private: \
        template<typename C> \
        static auto test(int) -> decltype((void)std::declval<C>().MEMBER, std::true_type()); \
        template<typename> static std::false_type test(...); \
    public: \
        static constexpr bool value = decltype(test<U>(0))::value; };

// 检查类型T是否存在名为MEMBER的公共静态成员
#define STATIC_ASSERT_HAS_PUBLIC_STATIC_MEMBER(T, MEMBER) \
    template<typename U> \
    class has_public_static_member_##MEMBER { \
    private: \
        template<typename C> \
        static auto test(int) -> decltype((void)C::MEMBER, std::true_type()); \
        template<typename> static std::false_type test(...); \
    public: \
        static constexpr bool value = decltype(test<U>(0))::value; };

// 检查类型T是否存在名为FUNC，返回类型为RET，参数为ARGS的公共成员函数
#define STATIC_ASSERT_HAS_MEMBER_FUNC(T, FUNC, RET, ...) \
    template<typename U> \
    class has_member_##FUNC { \
    private: \
        template<typename C> \
        static auto test(int) -> decltype( \
            std::is_same< \
                decltype(std::declval<C>().FUNC(std::declval<__VA_ARGS__>()...)), \
                RET \
            >(), std::true_type()); \
        template<typename> static std::false_type test(...); \
    public: \
        static constexpr bool value = decltype(test<U>(0))::value; };

// 检查类型T是否存在名为FUNC，返回类型为RET，参数为ARGS的公共静态成员函数
#define STATIC_ASSERT_HAS_STATIC_MEMBER_FUNC(T, FUNC, RET, ...) \
    template<typename U> \
    class has_static_member_##FUNC { \
    private: \
        template<typename C> \
        static auto test(int) -> decltype( \
            std::is_same< \
                decltype(C::FUNC(std::declval<__VA_ARGS__>()...)), \
                RET \
            >(), std::true_type()); \
        template<typename> static std::false_type test(...); \
    public: \
        static constexpr bool value = decltype(test<U>(0))::value; };


#endif