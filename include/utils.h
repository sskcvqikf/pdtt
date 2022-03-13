#ifndef PDTT_UTILS_HH_
#define PDTT_UTILS_HH_

#include <chrono>

struct Stats final {
  int all;
  int correct;
  std::chrono::duration<long, std::ratio<1, 1000000000>> ms;
};

#endif  // PDTT_UTILS_HH_
