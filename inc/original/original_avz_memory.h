#ifndef __ORIGINAL_AVZ_MEMORY_H__
#define __ORIGINAL_AVZ_MEMORY_H__

#include "avz_multi_platform.h"
#include  FILE_SHARED(avz_memory.h)

// This file(part) is strongly platform dependent.

// 女仆秘籍
class ATypeP(AMaidCheats, ORIGINAL) : public AOrderedExitFightHook<-1> {
public:
    // MC 前缀是 machine code 的缩写
    static constexpr uint32_t MC_CALL_PARTNER = 0x00F0B890;
    static constexpr uint32_t MC_DANCING = 0x0140B890;
    static constexpr uint32_t MC_MOVE = 0x00E9B890;
    static constexpr uint32_t MC_STOP = 0x838808B;

    static uint32_t& Phase() {
        return AMRef<uint32_t>(0x52DFC9);
    }

    // 召唤舞伴
    // 舞王不前进且每帧尝试召唤舞伴
    static void CallPartner() {
        Phase() = MC_CALL_PARTNER;
    }

    // 跳舞
    // 舞王不前进且不会召唤舞伴
    static void Dancing() {
        Phase() = MC_DANCING;
    }

    // 保持前进
    // 舞王一直前进
    static void Move() {
        Phase() = MC_MOVE;
    }

    // 停止女仆秘籍
    // 恢复游戏原样
    static void Stop() {
        Phase() = MC_STOP;
    }

protected:
    virtual void _ExitFight() override {
        Stop();
    }
} inline __amc;


#endif
