#ifndef __ORIGINAL_AVZ_CONNECTOR_H__
#define __ORIGINAL_AVZ_CONNECTOR_H__

#include "avz_multi_platform.h"
#include HEADER_SHARED(avz_connector.h)
#include HEADER_ORIGINAL(avz_pvz_struct.h)

// This file(part) is strongly platform dependent.

// Default arguments are given in shared/shared_avz_connector.h
template <typename Op>
    requires __AIsCoOpOrOp<Op>
AConnectHandle AConnect(AKey key, Op&& op, int priority, int runMode) {
    if (__AKeyManager::ToValidKey(key) != __AKeyManager::VALID)
        return AConnectHandle();
    auto wasPressed = std::make_shared<bool>(false);
    auto keyFunc = [key, wasPressed]() -> bool {
        bool isPressed = (GetAsyncKeyState(key) & 0x8000) == 0x8000;
        bool activate = isPressed && !*wasPressed;
        *wasPressed = isPressed;
        auto pvzHandle = AGetPvzBase()->MRef<HWND>(0x350);
        return (activate && GetForegroundWindow() == pvzHandle);              // 检测 pvz 是否为顶层窗口
    };
    auto handle = AConnect(std::move(keyFunc), std::forward<Op>(op), runMode, priority);
    __AKeyManager::AddKey(key, handle);
    return handle;
}

#endif
