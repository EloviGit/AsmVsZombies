#ifndef __SHARED_AVZ_PVZ_STRUCT_H__
#define __SHARED_AVZ_PVZ_STRUCT_H__

#include "avz_multi_platform.h"
#include FILE_SHARED(avz_types.h)
#include <Windows.h>
#include <cstdint>
#include <type_traits>


// struct APvzBase;         // 游戏主体
// struct AMainObject;      // 主要对象
// struct APlant;           // 植物
// struct AZombie;          // 僵尸
// struct ASeed;            // 种子（卡片）
// struct AItem;            // 收集物
// struct APlaceItem;       // 场地物品
// struct AMouseWindow;     // 鼠标窗口
// struct ATopMouseWindow;  // 顶层鼠标窗口
// struct ALetsRockBtn;     // lets_rock 按钮
// struct ASelectCardUi_m;  // 选卡界面在 main_object
// struct ASelectCardUi_p;  // 选卡界面在 pvz_base
// struct AMouse;           // 鼠标
// struct AMouseExtra;      // 鼠标额外属性
// struct AWords;           // 文字属性
// struct AAnimationMain;   // 动画主要对象
// struct AAnimationOffset; // 动画地址偏移
// struct AAnimation;       // 动画
// struct ACardSlot;        // 卡槽

class APvzStruct {
    __ADeleteCopyAndMove(APvzStruct);

public:
    template <typename T = APvzStruct>
    __ANodiscard T& MRef(uintptr_t addr) noexcept {
        return (T&)((uint8_t*)this)[addr];
    }

    template <typename T = APvzStruct>
    __ANodiscard T* MPtr(uintptr_t addr) noexcept {
        return *(T**)((uint8_t*)this + addr);
    }

    template <typename T = APvzStruct*>
    __ANodiscard T MVal(uintptr_t addr) noexcept {
        return (T)((uint8_t*)this + addr);
    }

    // MRef<T>(0x1, 0x2, 0x3) 形式
    template <typename T = APvzStruct, typename... Others>
    __ANodiscard T& MRef(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MRef<T>(others...);
    }

    template <typename T = APvzStruct, typename... Others>
    __ANodiscard T* MPtr(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MPtr<T>(others...);
    }

    template <typename T = APvzStruct*, typename... Others>
    __ANodiscard T MVal(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MVal<T>(others...);
    }

    template <typename T>
    void Write(const std::vector<T>& vec) {
        std::copy(vec.begin(), vec.end(), (T*)this);
    }

    template <typename T, typename Iter>
    void Write(Iter&& begin, Iter&& end) {
        std::copy(begin, end, (T*)this);
    }

    template <typename T>
    __ANodiscard auto Read(std::size_t size) {
        std::vector<T> vec(size);
        T* ptr = (T*)this;
        std::copy(ptr, ptr + size, vec.begin());
        return vec;
    }
};

template <typename T = APvzStruct>
__ANodiscard T& AMRef(uintptr_t addr) noexcept {
    return *(T*)(addr);
}

template <typename T = APvzStruct>
__ANodiscard T* AMPtr(uintptr_t addr) noexcept {
    return *(T**)(addr);
}

template <typename T = APvzStruct*>
__ANodiscard T AMVal(uintptr_t addr) noexcept {
    return (T)(addr);
}

// AMRef<T>(0x1, 0x2, 0x3) 形式
template <typename T = APvzStruct, typename... Others>
__ANodiscard T& AMRef(uintptr_t first, Others... others) noexcept {
    return AMPtr(first)->MRef<T>(others...);
}

template <typename T = APvzStruct, typename... Others>
__ANodiscard T* AMPtr(uintptr_t first, Others... others) noexcept {
    return AMPtr(first)->MPtr<T>(others...);
}

template <typename T = APvzStruct*, typename... Others>
__ANodiscard T AMVal(uintptr_t first, Others... others) noexcept {
    return AMPtr(first)->MVal<T>(others...);
}


#define __APvzStruct_UsingShortName(Platform)                           \
using APvzBase = ATypeP(APvzBase, Platform);                            \
using AMainObject = ATypeP(AMainObject, Platform);                      \
using APlant = ATypeP(APlant, Platform);                                \
using AZombie = ATypeP(AZombie, Platform);                              \
using ASeed = ATypeP(ASeed, Platform);                                  \
using AItem = ATypeP(AItem, Platform);                                  \
using APlaceItem = ATypeP(APlaceItem, Platform);                        \
using AMouseWindow = ATypeP(AMouseWindow, Platform);                    \
using ATopMouseWindow = ATypeP(ATopMouseWindow, Platform);              \
using ALetsRockBtn = ATypeP(ALetsRockBtn, Platform);                    \
using ASelectCardUi_m = ATypeP(ASelectCardUi_m, Platform);              \
using ASelectCardUi_p = ATypeP(ASelectCardUi_p, Platform);              \
using AMouse = ATypeP(AMouse, Platform);                                \
using AMouseExtra = ATypeP(AMouseExtra, Platform);                      \
using AWords = ATypeP(AWords, Platform);                                \
using AAnimationMain = ATypeP(AAnimationMain, Platform);                \
using AAnimationOffset = ATypeP(AAnimationOffset, Platform);            \
using AAnimation = ATypeP(AAnimation, Platform);                        \
using ACardSlot = ATypeP(ACardSlot, Platform);
// Using short name for platform independent code.

#define __APvzStruct_ForwardDeclare(Platform)                           \
struct ATypeP(APvzBase, Platform);                                      \
struct ATypeP(AMainObject, Platform);                                   \
struct ATypeP(APlant, Platform);                                        \
struct ATypeP(AZombie, Platform);                                       \
struct ATypeP(ASeed, Platform);                                         \
struct ATypeP(AItem, Platform);                                         \
struct ATypeP(APlaceItem, Platform);                                    \
struct ATypeP(AMouseWindow, Platform);                                  \
struct ATypeP(ATopMouseWindow, Platform);                               \
struct ATypeP(ALetsRockBtn, Platform);                                  \
struct ATypeP(ASelectCardUi_m, Platform);                               \
struct ATypeP(ASelectCardUi_p, Platform);                               \
struct ATypeP(AMouse, Platform);                                        \
struct ATypeP(AMouseExtra, Platform);                                   \
struct ATypeP(AWords, Platform);                                        \
struct ATypeP(AAnimationMain, Platform);                                \
struct ATypeP(AAnimationOffset, Platform);                              \
struct ATypeP(AAnimation, Platform);                                    \
struct ATypeP(ACardSlot, Platform);
// Forward declare all structs

__APvzStruct_ForwardDeclare(PLATFORM)
__APvzStruct_UsingShortName(PLATFORM)

__ANodiscard APvzBase* AGetPvzBase();
__ANodiscard AMainObject* AGetMainObject();
__ANodiscard AAnimation* AGetAnimationArray();

__ANodiscard inline bool AMainObjectIsValid() { return AGetMainObject() != nullptr; }
__ANodiscard inline bool APvzBaseIsValid() { return AGetPvzBase() != nullptr; }

// If an interface only needs pointers to pvz structs, use this file.
// If an interface needs member functions, use platform specific files instead.

#endif
