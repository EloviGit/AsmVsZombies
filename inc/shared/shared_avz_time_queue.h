#ifndef __SHARED_AVZ_TIME_QUEUE_H__
#define __SHARED_AVZ_TIME_QUEUE_H__

#include "avz_multi_platform.h"
#include HEADER_SHARED(avz_state_hook.h)
#include <map>
#include <optional>

struct __ABoolOperation {
    AOperation operation;
    bool isStopped = false;

    __ABoolOperation(const AOperation& operation)
        : operation(operation) {}

    __ABoolOperation(AOperation&& operation)
        : operation(std::move(operation)) {}
};

struct __ATimeOperation {
    AOperation operation;
    ATime time;

    __ATimeOperation(const AOperation& operation, const ATime& time)
        : operation(operation), time(time) {}

    __ATimeOperation(AOperation&& operation, const ATime& time)
        : operation(std::move(operation)), time(time) {}
};

struct __AOperationQueue {
    using RunOrderQueue = std::multimap<int, __ABoolOperation>;
    constexpr static int UNINIT = INT_MIN;
    RunOrderQueue queue;
    int calRefreshTime = UNINIT; // 计算得到的刷新时间，操作队列都用此时间
    int memRefreshTime = UNINIT; // 通过读内存得到的真实刷新时间，用于检查用户设定的波长是否正确
    int waveLength = -1;
};

using __ATimeIter = __AOperationQueue::RunOrderQueue::iterator;

class __AOpQueueManager : public AOrderedBeforeScriptHook<-32768>,
                          public AOrderedEnterFightHook<-32768>,
                          public AOrderedExitFightHook<-32768> {
public:
    bool isInitialized = false;
    std::vector<__AOperationQueue> queues;
    ATime startTime; // 脚本设定的开始时间
    int totalWave;
    std::optional<__ATimeIter> Push(const ATime& time, __ABoolOperation&& timeOp);
    void UpdateRefreshTime();
    void SetWavelength(const std::vector<ATime>& lst);
    void AssumeWavelength(const std::vector<ATime>& lst);
    void RunOperation();

protected:
    static std::optional<int> _GetNextWaveCountdown();
    void _PrintLog(const ATime& time, int nowTime);
    bool _CheckWavelength(const ATime& time);
    void _CheckAssumeWavelength(int wave);
    void _CalculateRefreshTime(int startWave);
    void _RecordRefresh(int wave, int refreshTime);
    virtual void _BeforeScript() override;
    virtual void _EnterFight() override;
    virtual void _ExitFight() override;
} inline __aOpQueueManager;

// 得到当前游戏的波数
__ANodiscard int ANowWave();
__ANodiscard int ANowWave(bool allowNegativeTime);

// 得到当前时间，读取失败返回 INT_MIN
// *** 注意得到的是以参数波刷新时间点为基准的相对时间
// *** 使用示例：
// ANowTime(1) -------- 得到以第一波刷新时间点为基准的当前时间
// ANowTime(2) -------- 得到以第二波刷新时间点为基准的当前时间
__ANodiscard int ANowTime(int wave);
__ANodiscard ATime ANowTime();
__ANodiscard ATime ANowTime(bool allowNegativeTime);

// 得到当前时间的延迟时间
__ANodiscard ATime ANowDelayTime(int delayTime);

// 设定特定波的波长
// *** 注意: 对最后一波无效
// 第 9、19、... 波的合法波长范围为 1346 - 5245，其他波为 601 - 3100
// *** 使用示例：
// ASetWavelength({ATime(1, 601), ATime(4, 1000)}) ----- 将第一波的波长设置为 601，将第四波的波长设置为 1000
inline void ASetWavelength(const std::vector<ATime>& lst) {
    __aOpQueueManager.SetWavelength(lst);
}

inline void ASetWavelength(int wave, int waveLength) {
    __aOpQueueManager.SetWavelength({{wave, waveLength}});
}

// 假定特定波的波长
// 本函数与 ASetWavelength 区别在于, 本函数不会对内存进行修改
// 只是可以让时间点的书写范围小于 -200, 如果真实的波长与假定的波长不一致, 则会报错
// *** 使用示例：
// AAssumeWavelength({ATime(1, 601), ATime(4, 1000)}) ----- 将第一波的波长假定为 601，将第四波的波长假定为 1000
inline void AAssumeWavelength(const std::vector<ATime>& lst) {
    __aOpQueueManager.AssumeWavelength(lst);
}

inline void AAssumeWavelength(int wave, int waveLength) {
    __aOpQueueManager.AssumeWavelength({{wave, waveLength}});
}


#endif
