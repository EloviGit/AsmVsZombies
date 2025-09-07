#ifndef __ORIGINAL_AVZ_LOGGER_H__
#define __ORIGINAL_AVZ_LOGGER_H__

#include "avz_multi_platform.h"
#include HEADER_ORIGINAL(avz_painter.h)
#include HEADER_SHARED(avz_logger.h)

NS_ORIGINAL_BEGIN(avz_logger)
USING_NS_ORIGINAL(avz_painter)


struct APvzGui {};

class ATickRunner;
template <>
class ALogger<APvzGui> : public AAbstractLogger {
public:
    ALogger();
    __ANodiscard APainter& GetPainter() { return _painter; }

    // 设置显示颜色
    // *** 使用示例:
    // SetColor(ALogLevel::INFO, AArgb(0xff, 0, 0, 0xff)) ------ 将 INFO 等级的显示颜色设置为蓝色
    // SetColor(ALogLevel::INFO, AArgb(0xff, 0, 0, 0xff), AArgb(0xff, 0, 0, 0)) ------ 将 INFO 等级的显示颜色设置为蓝色，并将背景色设置为黑色
    void SetColor(ALogLevel level, uint32_t textColor, uint32_t bkgColor = AArgb(0xaf, 0, 0, 0)) {
        _textColors[int(level)] = textColor;
        _rectColors[int(level)] = bkgColor;
    }

    // 设置背景颜色
    // *** 使用示例:
    // SetBkgColor(ALogLevel::INFO, AArgb(0xff, 0, 0, 0) ------- 将 INFO 等级的背景色设置为黑色
    void SetBkgColor(ALogLevel level, uint32_t bkgColor) {
        _rectColors[int(level)] = bkgColor;
    }

    // 设定显示持续时间
    // *** 使用示例:
    // SetRemainTime(100) ------- 将显示持续时间改为 100
    void SetRemainTime(int remainTime) {
        _remainTime = std::clamp(remainTime, 0, INT_MAX);
    }

    // 设定显示持续时间
    // *** 使用示例:
    // SetPos(50, 100) ------- 将显示位置更改为 (50, 100) [最大为 800, 600]
    void SetPos(int x, int y) {
        _pixelDisplay.x = std::clamp(x, 0, 800);
        _pixelDisplay.y = std::clamp(y, 0, 600);
    }

    // 设置平滑过渡速度
    // 默认值为 3
    void SetTransitSpeed(int speed) {
        _transitSpeed = std::clamp(speed, 1, INT_MAX);
    }

protected:
    uint32_t _textColors[4];
    uint32_t _rectColors[4];
    APainter _painter;
    int _remainTime = 500; // 控制显示的持续时间
    APixel _pixelDisplay = {10, 500};
    struct _Display {
        ALogLevel level;
        std::string str;
        int gameClock;
        int lineCnt = 0;
    };
    std::shared_ptr<ATickRunner> _tickRunner;
    std::deque<_Display> _displayList;
    int _curBottom = 0; // 为了平滑过渡使用的
    int _transitSpeed = 3;
    virtual void _BeforeScript() override;
    virtual void _Output(ALogLevel level, std::string&& str) override;
    void _ShowTick();
};

template <>
class ALogger<AMsgBox> : public AAbstractLogger {
protected:
    virtual void _Output(ALogLevel level, std::string&& str) override;
    virtual void _BeforeScript() override;
};


NS_END

#endif
