#ifndef __HAZ_BENCHMARK
#define __HAZ_BENCHMARK

#define RELEASE_MODE

#include <haz/Tools/Macro.hpp>

#include <chrono>
#include <map>

BEG_NAMESPACE_HAZ

#define CALCUL(name, block...)\
Benchmark::start();\
CALL_X_TIMES(Benchmark::iterations) block \
res[name] = Benchmark::stop();

class Benchmark {
public:
    struct STD_HAZ { long std; long haz; };
    typedef std::map<std::string, long> Result;
    typedef std::map<std::string, STD_HAZ> VersusResult;
    typedef std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> Time;

    static void all ();
    static Result vector ();
    static Result dynamicArray ();

    static void versus (std::string const& name, Result const& std_res, Result const& haz_res);
    static VersusResult joinResults (Result const& std_res, Result const& haz_res);

    static void start();
    static long stop();

    static const int iterations = 100000;

private:
    static Time current;
    static bool has_started;

    enum class Alignment { Left, Middle, Right };

    static std::string adjust(std::string const& s, unsigned int size, std::string const& fill = " ", Alignment align = Alignment::Middle);
};

END_NAMESPACE_HAZ

#endif