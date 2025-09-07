#ifndef __SHARED_AVZ_LOGGER_H__
#define __SHARED_AVZ_LOGGER_H__

#include "avz_multi_platform.h"
#include HEADER_SHARED(avz_state_hook.h)

#include <deque>
#include <format>
#include <fstream>
#include <sstream>
#include <string_view>


enum class ALogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
};

class AAbstractLogger : public AOrderedBeforeScriptHook<-32767> {
public:
    __ANodiscard const std::string& GetPattern() const {
        return _pattern;
    }

    void SetPattern(std::string_view pattern) {
        _pattern = pattern;
    }

    void SetHeaderStyle(std::string_view headerStyle) {
        _headerStyle = headerStyle;
    }

    void SetLevel(const std::vector<ALogLevel>& levelVec) {
        _level = 0;
        for (auto&& level : levelVec)
            _level |= (1 << int(level));
    }

    void SetSuffix(const std::string& suffix) { _suffix = suffix; }

    template <typename FormatStr, typename... Args>
    void Info(FormatStr&& formatStr, Args&&... args) {
        _Format(ALogLevel::INFO, std::forward<FormatStr>(formatStr), std::forward<Args>(args)...);
    }

    template <typename FormatStr, typename... Args>
    void Debug(FormatStr&& formatStr, Args&&... args) {
        _Format(ALogLevel::DEBUG, std::forward<FormatStr>(formatStr), std::forward<Args>(args)...);
    }

    template <typename FormatStr, typename... Args>
    void Warning(FormatStr&& formatStr, Args&&... args) {
        _Format(ALogLevel::WARNING, std::forward<FormatStr>(formatStr), std::forward<Args>(args)...);
    }

    template <typename FormatStr, typename... Args>
    void Error(FormatStr&& formatStr, Args&&... args) {
        _Format(ALogLevel::ERROR, std::forward<FormatStr>(formatStr), std::forward<Args>(args)...);
    }

protected:
    std::string _pattern;
    std::string _headerStyle;
    uint8_t _level = 0b1111; // 每一个 bit 代表这个水平的日志开不开(1是开)
    std::string _bufStr;
    std::string _suffix = "\n";
    const std::vector<std::string> _levelStr = {
        "INFO",
        "DEBUG",
        "WARNING",
        "ERROR",
    };
    virtual void _BeforeScript() override;
    virtual void _Output(ALogLevel level, std::string&& str) = 0;

    static void _Replace(std::string& content, std::string_view pattern, std::string_view replaceStr);

    std::string _CreateHeader(ALogLevel level);

    void _Format(ALogLevel level, std::string formatStr, auto&&... args) {
        if (((1 << int(level)) & _level) == 0)
            return;
        auto header = _CreateHeader(level);
        _Replace(formatStr, _pattern, "{}");
        std::string message;
        try {
            message = std::vformat(formatStr + _suffix, std::make_format_args(std::forward<decltype(args)>(args)...));
        } catch (const std::format_error& e) {
            message = "格式化错误: " + std::string(e.what());
        }
        _Output(level, header + message);
    }
};

struct AFile {};
struct AConsole {};
struct AMsgBox {
    static void Show(const std::string& str) {
        MessageBoxW(nullptr, AStrToWstr(str).c_str(), L"AMsgBox", MB_OK);
    }
};


template <typename T>
class ALogger;

template <>
class ALogger<AFile> : public AAbstractLogger, public AOrderedExitFightHook<32767> {
public:
    ALogger(const std::string& fileName)
        : _fileName(fileName) {}

    // 清除文件中的所有内容
    // return true: 清除成功
    // return false: 清除失败
    bool Clear();

protected:
    virtual void _BeforeScript() override;
    virtual void _ExitFight() override;
    std::string _fileName;
    std::wofstream _outFile;
    virtual void _Output(ALogLevel level, std::string&& str) override;
};


template <>
class ALogger<AConsole> : public AAbstractLogger {
public:
    ALogger();
    ~ALogger();
    // 设置显示颜色
    // *** 使用示例:
    // SetColor(ALogLevel::INFO, FOREGROUND_BLUE) ------ 将 INFO 等级的显示颜色设置为蓝色
    void SetColor(ALogLevel level, uint32_t color) {
        _color[int(level)] = color;
    }

protected:
    uint32_t _color[4];
    static bool _isAllocateConsole;
    HANDLE _handle = nullptr;
    virtual void _Output(ALogLevel level, std::string&& str) override;
};

inline AAbstractLogger* aLogger;

// 注意这个函数返回的是对象指针
inline AAbstractLogger* AGetInternalLogger() {
    return aLogger;
}

inline void ASetInternalLogger(AAbstractLogger& logger) {
    aLogger = &logger;
}



#endif
