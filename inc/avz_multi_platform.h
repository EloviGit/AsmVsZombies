#ifndef __AVZ_MULTI_PLATFORM_H__
#define __AVZ_MULTI_PLATFORM_H__

// #include "avz_compile_time_checks.h"

#define __AEXPAND(x)                    x
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
// 3. Define HEADER_NEW_PLATFORM(header) and NS_NEW_PLATFORM(name) macros
// 4. Implement your code in inc/new_platform/ and src/new_platform/
// 5. All files need to include avz_multi_platform.h
// 6. Wrap all your code in new_platform_avz_XX.h, .cpp in namespace NS_NEW_PLATFORM(avz_XX)
// 7. To include inc/new_platform/newplatform_avz_XX.h, use HEADER_NEW_PLATFORM(avz_XX)

#ifdef USE_NS
#undef USE_NS
#endif

#define __ORIGINAL_IDENTIFIER               original
#define HEADER_ORIGINAL(header)             __ANEW_FILENAME(__ORIGINAL_IDENTIFIER, header)
#define NS_ORIGINAL(name)                   __AJOIN( __ORIGINAL_IDENTIFIER, ns)
// I used to wrap each {platform_avz_XXX.h, .cpp} into namespace unique to XXX(original_XXX), but it seems unnecessary;
// So now I wrap all {platform_avz_XXX.h, .cpp} into namespace with respect to platform only(original_)

#define __PVZ_EMULATOR_IDENTIFIER           pvz_emulator
#define HEADER_PVZ_EMULATOR(header)         __ANEW_FILENAME(__PVZ_EMULATOR_IDENTIFIER, header)
#define NS_PVZ_EMULATOR(name)               __AJOIN( __PVZ_EMULATOR_IDENTIFIER, ns)

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
#define NS_PLATFORM(name)                   __AJOIN( __APlatformIdentifier, name)
#define NS_AVZ(name)                        __AJOIN(avz, name)

#define HEADER_SHARED(header)               __ANEW_FILENAME(shared, header)


#ifdef USE_NS
#define NS_ORIGINAL_BEGIN(name)             namespace NS_ORIGINAL(name) {
#define NS_PVZ_EMULATOR_BEGIN(name)         namespace NS_PVZ_EMULATOR(name) {
#define NS_AVZ_BEGIN(name)                  namespace NS_AVZ(name) {
#define NS_END                              }
#define USING_NS_ORIGINAL(name)             using namespace NS_ORIGINAL(name);
#define USING_NS_PVZ_EMULATOR(name)         using namespace NS_PVZ_EMULATOR(name);
#define USING_NS_PLATFORM(name)             using namespace NS_PLATFORM(name);
#define USING_NS_AVZ(name)                  using namespace NS_AVZ(name);
#else
#define NS_ORIGINAL_BEGIN(name)
#define NS_PVZ_EMULATOR_BEGIN(name)
#define NS_AVZ_BEGIN(name)
#define NS_END
#define USING_NS_ORIGINAL(name)
#define USING_NS_PVZ_EMULATOR(name)
#define USING_NS_PLATFORM(name)             
#define USING_NS_AVZ(name)
#endif

#define PACK_NS_AVZ(name)                   \
NS_AVZ_BEGIN(name)                          \
USING_NS_PLATFORM(name)                     \
NS_END                                      \
USING_NS_AVZ(name)                          \




// // ASTATIC_ASSERT_EXISTS_TYPE: 编译期检查标识符TYPE是否有定义、或类型TYPE是否存在
// #define STATIC_ASSERT_EXISTS_TYPE(TYPE) \
// template<typename = void> struct __AID_TEMP(TYPE##type_exists) : std::false_type {}; \
// template<> struct __AID_TEMP(TYPE##type_exists)<decltype(sizeof(TYPE), void())> : std::true_type {}; \
// static_assert(__AID_TEMP(TYPE##type_exists)<>::value, "Type " #TYPE " does not exist.");


// // 检查类型TYPE是否存在名为MEMBER的public成员
// #define STATIC_ASSERT_HAS_PUBLIC_MEMBER(TYPE, MEMBER) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_member_##MEMBER) = \
// requires(T t) { t.MEMBER; }; \
// static_assert(__AID_TEMP(TYPE##_has_public_member_##MEMBER)<TYPE>, \
// "Type " #TYPE " does not have public member named " #MEMBER);


// // 检查类型TYPE是否存在名为MEMBER、类型为MTYPE的public成员
// #define STATIC_ASSERT_HAS_PUBLIC_MEMBER_OF_TYPE(TYPE, MEMBER, MTYPE) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_member_##MEMBER) = \
// std::is_same_v<decltype(std::declval<T>().MEMBER), MTYPE>; \
// static_assert(__AID_TEMP(TYPE##_has_public_member_##MEMBER)<TYPE>, \
// "Type " #TYPE " does not have public member named " #MEMBER " of type " #MTYPE);


// // 检查类型TYPE是否存在名为MEMBER的public static成员
// #define STATIC_ASSERT_HAS_PUBLIC_STATIC_MEMBER(TYPE, MEMBER) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_static_member_##MEMBER) = \
// requires { T::MEMBER; }; \
// static_assert(__AID_TEMP(TYPE##_has_public_static_member_##MEMBER)<TYPE>, \
// "Type " #TYPE " does not have public static member named " #MEMBER);


// // 检查类型TYPE是否存在名为MEMBER、类型为MTYPE的public static成员
// #define STATIC_ASSERT_HAS_PUBLIC_STATIC_MEMBER_OF_TYPE(TYPE, MEMBER, MTYPE) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_static_member_##MEMBER) = \
// std::is_same_v<decltype(T::MEMBER), MTYPE>; \
// static_assert(__AID_TEMP(TYPE##_has_public_static_member_##MEMBER)<TYPE>, \
// "Type " #TYPE " does not have public static member named " #MEMBER " of type " #MTYPE);


// // 检查类型TYPE是否存在名为FUNC，返回类型为RET，参数为...的public成员函数
// #define STATIC_ASSERT_HAS_PUBLIC_MEMBER_FUNC(TYPE, FUNC, RET, ...) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_member_func) = \
// requires { {&T::FUNC} -> std::same_as<RET(T::*)(__VA_ARGS__)>; }; \
// static_assert( __AID_TEMP(TYPE##_has_public_member_func)<TYPE>, \
// "Type " #TYPE " does not have public member function named " #FUNC " with return type " #RET " and parameters (" #__VA_ARGS__ ")");


// // 检查类型TYPE是否存在名为FUNC，返回类型为RET，参数为...的public static成员函数
// #define STATIC_ASSERT_HAS_PUBLIC_STATIC_MEMBER_FUNC(TYPE, FUNC, RET, ...) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_static_member_func) = \
// requires { {&T::FUNC} -> std::same_as<RET(*) (__VA_ARGS__)>; }; \
// static_assert( __AID_TEMP(TYPE##_has_public_static_member_func)<TYPE>, \
// "Type " #TYPE " does not have public static member function named " #FUNC " with return type " #RET " and parameters (" #__VA_ARGS__ ")");


// //检查类型TYPE是否存在参数为...的public构造函数
// #define STATIC_ASSERT_HAS_PUBLIC_CTOR(TYPE, ...) \
// template<typename T> concept __AID_TEMP(TYPE##_has_public_ctor) = \
// std::constructible_from<T __VA_OPT__(,) __VA_ARGS__>; \
// static_assert( __AID_TEMP(TYPE##_has_public_ctor)<TYPE>, \
// "Type " #TYPE " does not have public constructor with parameters (" #__VA_ARGS__ ")");

// //检查类型是否已经删除了移动和拷贝语义
// template<typename T> concept __AHasDeletedCopyAndMove = \
// !std::is_move_constructible_v<T> && !std::is_move_assignable_v<T> \
// && !std::is_copy_constructible_v<T> && !std::is_copy_assignable_v<T>;

// #define STATIC_ASSERT_COPY_AND_MOVE_DELETED(TYPE) \
// static_assert(__AHasDeletedCopyAndMove<TYPE>, \
// "Type " #TYPE " 's copy and move constructor and assignment operator are not fully deleted.");




// #define __AMEMBER_FUNC_CHECK(TYPE, _PREVQ, FUNC, _POSTQ, RET, ...) \
// std::is_same_v<decltype(std::declval<TYPE>), RET(TYPE::*)(__VA_ARGS__)_POSTQ>

// #define __AFREE_FUNC_CHECK(FUNC, _POSTQ, RET, ...) \






// cannot allow to happen: TYPE is empty and _PREVQ is static
// either TYPE is non-empty, or _PREVQ is empty (non static)
// FUNC must be non-empty
// if type is empty: this is a normal function:
// static qualifier becomes useless.




#endif