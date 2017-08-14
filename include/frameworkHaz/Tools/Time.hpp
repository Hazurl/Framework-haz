#ifndef __HAZ_TIME
#define __HAZ_TIME

#include <chrono>
#include <frameworkHaz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

class Time {
public:

    Time();
    ~Time();

    long deltaTime() const;
    long time () const;

    long deltaTime_s() const;
    long deltaTime_ms() const;
    long deltaTime_us() const;
    long deltaTime_ns() const;

    long time_s () const;
    long time_ms () const;
    long time_us () const;
    long time_ns () const;

    void update();

private:
    long long frame;

    const std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> startTime;
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> lastTime;
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> lastlastTime;
};

END_NAMESPACE_HAZ

#endif