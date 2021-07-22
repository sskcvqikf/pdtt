#ifndef PDTT_STATISTICS_MODE_HH_
#define PDTT_STATISTICS_MODE_HH_

#include <chrono>
#include <string>
#include <sstream>

#include "utils.hh"
#include "window.hh"

struct StatisticsMode
{
    StatisticsMode(const StatisticsMode &) = delete;

    StatisticsMode(std::string format, Stats stat);
    ~StatisticsMode();


    auto verbose() const
        -> void;

private:
    std::string format_;
    Window window_;
    Stats stat_;
};
#endif // PDTT_STATISTICS_MODE_HH_
