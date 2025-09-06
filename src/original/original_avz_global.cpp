#include "avz_multi_platform.h"
#include HEADER_ORIGINAL(libavz.h)

#include <codecvt>

NS_ORIGINAL_BEGIN(avz_global)

__AInternalGlobal __aig;

bool ARangeIn(int num, const std::vector<int>& lst) {
    for (auto _num : lst)
        if (_num == num)
            return true;
    return false;
}

std::wstring AStrToWstr(const std::string& input) {
    std::wstring wstr;
    wstr.resize(MultiByteToWideChar(CP_UTF8, 0, input.c_str(), input.length(), NULL, 0) + 1);
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), input.length(), wstr.data(), wstr.size());
    for (; !wstr.empty() && wstr.back() == 0;)
        wstr.pop_back();
    return wstr;
}

std::string AWStrToStr(const std::wstring& input) {
    std::string str;
    str.resize(WideCharToMultiByte(CP_UTF8, 0, input.c_str(), input.length(), NULL, 0, NULL, FALSE) + 1);
    WideCharToMultiByte(CP_UTF8, 0, input.c_str(), input.length(), str.data(), str.size(), NULL, FALSE);
    for (; !str.empty() && str.back() == 0;)
        str.pop_back();
    return str;
}

std::u32string AStrToU32str(const std::string& input) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(input);
}

std::string AU32StrToStr(const std::u32string& input) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.to_bytes(input);
}

NS_END
