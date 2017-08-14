#include <frameworkHaz/Benchmark/Benchmark.hpp>

BEG_NAMESPACE_HAZ

bool Benchmark::has_started = false;
Benchmark::Time Benchmark::current = Benchmark::Time();

void Benchmark::all () {
    std::cout << "Base on " << Benchmark::iterations << " iterations" << std::endl;
    Benchmark::start();
    CALL_X_TIMES(Benchmark::iterations) {}
    std::cout << "Empty Time : " << Benchmark::stop() << " ns" << std::endl;
    std::cout << "Release mode "
#ifdef RELEASE_MODE
    "enabled"
#else
    "disabled"
#endif
    << std::endl;
    Benchmark::versus("Dynamic Array", Benchmark::vector(), Benchmark::dynamicArray());
}

void Benchmark::versus (std::string const& name, Benchmark::Result const& std_res, Benchmark::Result const& haz_res) {
    // ╠ ╔ ║ ╗ ═ ╣ ╦ ╩ ╬ ╚ ╝
    Benchmark::VersusResult res = Benchmark::joinResults(std_res, haz_res);

    std::string straight = Benchmark::adjust("", 20, "═");
    std::string empty = Benchmark::adjust("", 20);
    std::cout << "╔" << straight << "╦" << straight << "╦" << straight << "╦" << straight << "╗" << std::endl;
    std::cout << "║\033[34m\033[1m" << Benchmark::adjust(name, 20) << "\033[0m║" << Benchmark::adjust("STD", 20) << "║" << Benchmark::adjust("HAZ", 20) << "║" << Benchmark::adjust("Difference", 20) << "║" << std::endl;
    std::cout << "╠" << straight << "╬" << straight << "╬" << straight << "╬" << straight << "╣" << std::endl;

    for (auto& p : res) {
        std::cout << "║" << Benchmark::adjust(p.first, 20);
        std::cout << "║" << Benchmark::adjust(std::to_string(p.second.std) + " ns ", 20, " ", Benchmark::Alignment::Right);
        std::cout << "║" << Benchmark::adjust(std::to_string(p.second.haz) + " ns ", 20, " ", Benchmark::Alignment::Right);
        long diff = p.second.haz - p.second.std;
        std::string diff_str = std::to_string(diff) + " ns ";
        std::cout << "║";
        if (diff >= 0) {
            diff_str = "+" + diff_str;
            std::cout << "\033[31m";
        } else {
            std::cout << "\033[32m";
        }
        std::cout << Benchmark::adjust(diff_str, 20, " ", Benchmark::Alignment::Right);
        std::cout << "\033[0m║" << std::endl;
    }
    std::cout << "╚" << straight << "╩" << straight << "╩" << straight << "╩" << straight << "╝" << std::endl;
}

Benchmark::VersusResult Benchmark::joinResults (Benchmark::Result const& std_res, Benchmark::Result const& haz_res) {
    Benchmark::VersusResult res;
    for (auto& pair : std_res) {
        if (haz_res.find(pair.first) != haz_res.end()) {
            res[pair.first] = { pair.second, haz_res.at(pair.first) };
        } else {
            res[pair.first] = { pair.second, -1 };
        }
    }

    for (auto& pair : haz_res) {
        if (res.find (pair.first) == res.end())
            res[pair.first] = { -1, pair.second };
    }

    return res;
}

Benchmark::Result Benchmark::dynamicArray () {
    Benchmark::Result res;

    {
        CALCUL("Constructor", {
            DynamicArray<int>();
        });
    }
    {
        auto a = DynamicArray<int>();
        CALCUL("Push", {
            a.push(__i__);
        });
    }
    {
        auto a = DynamicArray<int>();
        CALCUL("Reserve", {
            a.reserve(__i__);
        });
    }
    {
        auto a = DynamicArray<int>();
        CALCUL("Resize", {
            a.resize(__i__);
        });
    }
    {
        auto a = DynamicArray<int>();
        a.push({1, 2, 3});
        CALCUL("Access []", {
            a[1];
        });
    }

    return res;
}

Benchmark::Result Benchmark::vector () {
    Benchmark::Result res;

    {
        CALCUL("Constructor", {
            std::vector<int>();
        });
    }
    {
        auto a = std::vector<int>();
        CALCUL("Push", {
            a.push_back(__i__);
        });
    }
    {
        auto a = std::vector<int>();
        CALCUL("Reserve", {
            a.reserve(__i__);
        });
    }
    {
        auto a = std::vector<int>();
        CALCUL("Resize", {
            a.resize(__i__);
        });
    }
    {
        auto a = std::vector<int>({1, 2, 3});
        CALCUL("Access []", {
            a[1];
        });
    }

    return res;
}

void Benchmark::start () {
    Benchmark::has_started = true;
    Benchmark::current = std::chrono::high_resolution_clock::now();
}

long Benchmark::stop () {
    HAZ_ASSERT_MSG("Chrono not started", Benchmark::has_started);

    Benchmark::has_started = false;
    Benchmark::Time end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - Benchmark::current).count();
}

std::string Benchmark::adjust(std::string const& s, unsigned int size, std::string const& fill, Benchmark::Alignment align) {
    if (s.size() > size) {
        return s.substr(0, size);
    } else {
        std::string _s = s;
        for (unsigned int i = s.size(); i < size; ++i) {
            if (align == Benchmark::Alignment::Left || (align == Benchmark::Alignment::Middle && i % 2 == 0))
                _s += fill;
            else
                _s = fill + _s;
        }
        return _s;
    }
}

END_NAMESPACE_HAZ