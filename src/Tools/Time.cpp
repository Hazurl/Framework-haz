#include <frameworkHaz/Tools/Time.hpp>

BEG_NAMESPACE_HAZ

Time::Time() : frame(0), startTime(std::chrono::high_resolution_clock::now()), lastTime(startTime), lastlastTime(startTime) {

}

Time::~Time() {

}

void Time::update() {
    lastlastTime = lastTime;
    lastTime = std::chrono::high_resolution_clock::now();
    frame++;
}

long Time::deltaTime_s () const {
    return std::chrono::duration_cast<std::chrono::seconds>(lastTime - lastlastTime).count();
}

long Time::time_s () const {
    return std::chrono::duration_cast<std::chrono::seconds>(lastTime - startTime).count();
}

long Time::deltaTime_ms () const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(lastTime - lastlastTime).count();
}

long Time::time_ms () const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(lastTime - startTime).count();
}

long Time::deltaTime_us () const {
    return std::chrono::duration_cast<std::chrono::microseconds>(lastTime - lastlastTime).count();
}

long Time::time_us () const {
    return std::chrono::duration_cast<std::chrono::microseconds>(lastTime - startTime).count();
}

long Time::deltaTime_ns () const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(lastTime - lastlastTime).count();
}

long Time::time_ns () const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(lastTime - startTime).count();
}

long Time::deltaTime () const {
    return deltaTime_ms();
}

long Time::time () const {
    return time_ms();
}

END_NAMESPACE_HAZ