#ifndef __HAZ_SOURCE_INF
#define __HAZ_SOURCE_INF

#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

#define SOURCE_INFO_LIST __LINE__, __PRETTY_FUNCTION__, __FILE__
#define SOURCE_INFO ::haz::SourceInfo(SOURCE_INFO_LIST)

struct SourceInfo {
    inline SourceInfo(unsigned int line, const char* func, const char* file) :
        file(file),
        func(func),
        line(line)
    {}

    const char* const file;
    const char* const func;
    const unsigned int line;
};

std::ostream& operator << (std::ostream& os, SourceInfo const& s) {
    return os << "in " << s.func << " from " << s.file << " at " << s.line;
}

END_NAMESPACE_HAZ

#endif