#ifndef PDTT_STATISTICS_MODE_HH_
#define PDTT_STATISTICS_MODE_HH_

#include <chrono>
#include <sstream>
#include <string>

#include "utils.h"
#include "window.h"

struct StatisticsMode {
  StatisticsMode(const StatisticsMode &) = delete;

  StatisticsMode(std::string format, Stats stat);
  ~StatisticsMode();

  auto verbose() const -> void;

 private:
  std::string format_;
  Window window_;
  Stats stat_;
};
#endif  // PDTT_STATISTICS_MODE_HH_
