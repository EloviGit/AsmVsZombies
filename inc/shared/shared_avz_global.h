#ifndef __SHARED_AVZ_GLOBAL_H__
#define __SHARED_AVZ_GLOBAL_H__

#include "avz_multi_platform.h"
#include FILE_SHARED(avz_exception.h)
#include <Windows.h>
#include <algorithm>
#include <map>
#include <random>
#include <string>

#undef min
#undef max
#undef ERROR


__ANodiscard std::wstring AStrToWstr(const std::string& input);
__ANodiscard std::string AWStrToStr(const std::wstring& input);
__ANodiscard std::u32string AStrToU32str(const std::string& input);
__ANodiscard std::string AU32StrToStr(const std::u32string& input);

template <>
struct std::formatter<std::u32string> : std::formatter<std::string> {
    auto format(const std::u32string& str, auto& ctx) const {
        return formatter<std::string>::format(AU32StrToStr(str), ctx);
    }
};

template <>
struct std::formatter<std::u32string_view> : std::formatter<std::string> {
    auto format(std::u32string_view str, auto& ctx) const {
        return formatter<std::string>::format(AU32StrToStr(std::u32string(str)), ctx);
    }
};

template <>
struct std::formatter<char32_t> : std::formatter<std::string> {
    auto format(char32_t ch, auto& ctx) const {
        return formatter<std::string>::format(AU32StrToStr(std::u32string(1, ch)), ctx);
    }
};

// *** 函数功能：判断数字范围
// *** 使用示例：
// RangeIn(wave, {1,2,3})------如果波数在 1 2 3 范围里返回 true
__ANodiscard bool ARangeIn(int num, const std::vector<int>& lst);

template <typename T>
__ANodiscard std::vector<T> __AErase(const std::vector<T>& vec, const std::vector<T>& targets) {
    std::vector<T> result;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), [&](const T& x) {
        return std::find(targets.begin(), targets.end(), x) == targets.end();
    });
    return result;
}

template <typename T>
__ANodiscard std::vector<T> __AMoveToTop(const std::vector<T>& vec, const std::vector<T>& targets) {
    std::vector<T> result;
    result.insert(result.end(), targets.begin(), targets.end());
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), [&](const T& x) {
        return std::find(targets.begin(), targets.end(), x) == targets.end();
    });
    return result;
}

template <typename T>
__ANodiscard std::vector<T> __AMoveToBottom(const std::vector<T>& vec, const std::vector<T>& targets) {
    std::vector<T> result;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), [&](const T& x) {
        return std::find(targets.begin(), targets.end(), x) == targets.end();
    });
    result.insert(result.end(), targets.begin(), targets.end());
    return result;
}

class __ATickManager;

struct __AInternalGlobal {
    HINSTANCE hInstance = nullptr;
    // 这个指针指向的是一个数组 !!!
    // 大小为 ATickRunner::__COUNT
    __ATickManager* tickManagers = nullptr;
    // 用于 class __AObjectPool 的唯一对象标识
    std::size_t objId = 0;
    auto& GetInitOps() {
        static std::vector<AOperation> _;
        return _;
    }
} inline __aig;

// Never referred function. Is it necessary?
inline HINSTANCE AGetDllInstance() {
    return __aig.hInstance;
}

template <typename Op>
inline void __ARegisterInitOp(Op&& op) {
    __aig.GetInitOps().emplace_back(std::forward<Op>(op));
}

// 随机数产生类
template <typename Engine = std::default_random_engine>
class ARandom {
public:
    ARandom(uint32_t seed)
        : _engine(seed) {}

    ARandom()
        : _engine(std::random_device()()) {}

    void SetSeed(uint32_t seed) {
        _engine.seed(seed);
    }

    // 生成范围为 [left, right) 的随机整数，注意区间为左闭右开
    template <typename Left, typename Right, typename Common = std::common_type_t<Left, Right>>
        requires std::is_integral_v<Common>
    __ANodiscard Common Integer(Left left, Right right) {
        return std::uniform_int_distribution<Common>(left, right - 1)(_engine);
    }

    template <typename T = int>
    __ANodiscard auto Integer(T right = std::numeric_limits<T>::max()) {
        return Integer(0, right);
    }

    // 生成范围为 [left, right) 的随机浮点数，注意区间为左闭右开
    template <typename Left, typename Right, typename Common = std::common_type_t<Left, Right, float>>
    __ANodiscard Common Real(Left left, Right right) {
        return std::uniform_real_distribution<Common>(left, right)(_engine);
    }

    template <typename T = double, typename Common = std::common_type_t<T, float>>
    __ANodiscard Common Real(T right = 1.0) {
        return Real(Common(0.0), right);
    }

    template <typename Left, typename Right, typename Common = std::common_type_t<Left, Right>>
    __ANodiscard auto operator()(Left left, Right right) {
        if constexpr (std::is_integral_v<Common>)
            return Integer(left, right);
        else
            return Real(left, right);
    }

    template <typename T = double>
    __ANodiscard auto operator()(T right = 1.0) {
        if constexpr (std::is_integral_v<T>)
            return Integer(right);
        else
            return Real(right);
    }

    template <typename Iter>
    __ANodiscard auto Choice(Iter begin, Iter end) {
        auto diff = std::distance(begin, end);
        if (diff <= 0)
            throw AException("ARandom::Choice 选择范围非法");
        return *std::next(begin, Integer(diff));
    }

    template <typename Iter>
    __ANodiscard auto Choice(Iter begin, Iter end, std::size_t n) {
        using Type = std::remove_cvref_t<decltype(*begin)>;
        std::vector<Type> ret(n);
        for (std::size_t i = 0; i < n; ++i)
            ret[i] = Choice(begin, end);
        return ret;
    }

    // 从数组中随机选择 1 个数
    __ANodiscard auto Choice(auto&& container) {
        return Choice(container.begin(), container.end());
    }

    // 从数组中随机可重复选择 n 个数
    __ANodiscard auto Choice(auto&& container, std::size_t n) {
        return Choice(container.begin(), container.end(), n);
    }

    template <typename T>
    __ANodiscard auto Choice(std::initializer_list<T> ls) {
        return Choice(ls.begin(), ls.end());
    }

    template <typename T>
    __ANodiscard auto Choice(std::initializer_list<T> ls, int n) {
        return Choice(ls.begin(), ls.end(), n);
    }

    // 从数组中随机不重复选择 n 个数
    template <typename Iter>
    __ANodiscard auto Sample(Iter begin, Iter end, std::size_t n) {
        auto diff = std::distance(begin, end);
        if (diff < n)
            throw AException("ARandom::Sample 选择范围非法");
        using Type = std::remove_cvref_t<decltype(*begin)>;
        std::vector<Type> ret(n);
        std::sample(begin, end, ret.begin(), n, _engine);
        return ret;
    }

    // 从数组中随机不重复选择 n 个数
    __ANodiscard auto Sample(auto&& container, std::size_t n) {
        return Sample(container.begin(), container.end(), n);
    }

    template <typename T>
    __ANodiscard auto Sample(std::initializer_list<T> ls, int n) {
        return Sample(ls.begin(), ls.end(), n);
    }

    template <typename Iter>
    void Shuffle(Iter begin, Iter end) {
        std::shuffle(begin, end, _engine);
    }

    void Shuffle(auto&& container) {
        Shuffle(container.begin(), container.end());
    }

    template <typename T>
    void Shuffle(std::initializer_list<T> ls) {
        Shuffle(ls.begin(), ls.end());
    }

    auto&& GetEngine() {
        return _engine;
    }

protected:
    Engine _engine;
};

inline ARandom aRandom;

template <typename... Ts>
class AAlwaysTrue {
public:
    bool operator()(Ts&&...) const {
        return true;
    }
};

#endif
