#ifndef __ORIGINAL_AVZ_CONNECTOR_H__
#define __ORIGINAL_AVZ_CONNECTOR_H__

#include "avz_multi_platform.h"
#include HEADER_SHARED(avz_coroutine.h)
#include HEADER_SHARED(avz_tick_runner.h)
#include HEADER_SHARED(avz_connector.h)


class __AKeyManager : public AOrderedExitFightHook<-1> {
public:
    enum KeyState {
        VALID,
        UNKNOWN,
        REPEAT,
    };
    __AKeyManager();
    static KeyState ToValidKey(AKey& key);
    static void AddKey(AKey key, AConnectHandle connectHandle) {
        _keyMap.emplace(key, connectHandle);
    }
    static const std::string& ToName(AKey key) {
        return _keyVec[key];
    }

protected:
    static std::vector<std::string> _keyVec;
    static std::unordered_map<AKey, AConnectHandle> _keyMap;
    virtual void _ExitFight() override {
        _keyMap.clear();
    }
};

inline __AKeyManager __akm; // AStateHook

template <typename Op>
    requires __AIsCoOpOrOp<Op>
AConnectHandle AConnect(AKey key, Op&& op, int priority = 0, int runMode = ATickRunner::GLOBAL) {
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
