#include "avz_multi_platform.h"
#include HEADER_SHARED(libavz.h)

void AAbstractLogger::_BeforeScript() {
    _pattern = "#";
    _headerStyle = "[{wave}, {time}][{level}] ";
}

void AAbstractLogger::_Replace(std::string& content, std::string_view pattern, std::string_view replaceStr) {
    if (pattern.empty())
        return;
    size_t idx = 0;
    while (true) {
        idx = content.find(pattern, idx);
        if (idx == std::string::npos)
            break;
        content.replace(idx, pattern.size(), replaceStr);
        idx += replaceStr.size();
    }
}

std::string AAbstractLogger::_CreateHeader(ALogLevel level) {
    std::string headerFormat = _headerStyle;
    _Replace(headerFormat, _pattern + "wave", "{0}");
    _Replace(headerFormat, "{wave", "{0");
    _Replace(headerFormat, _pattern + "time", "{1}");
    _Replace(headerFormat, "{time", "{1");
    _Replace(headerFormat, _pattern + "level", "{2}");
    _Replace(headerFormat, "{level", "{2");
    _Replace(headerFormat, _pattern + "flag", "{3}");
    _Replace(headerFormat, "{flag", "{3");
    ATime now = ANowTime(false);
    int flag = AGetMainObject() ? AGetMainObject()->CompletedRounds() * 2 : 0;
    return std::vformat(headerFormat, std::make_format_args(now.wave, now.time, _levelStr[int(level)], flag));
}