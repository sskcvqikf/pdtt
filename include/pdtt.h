#ifndef PDTT_PDTT_HH_
#define PDTT_PDTT_HH_

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>

#include "default_mode.h"
#include "dictionary.h"
#include "random_letters_mode.h"
#include "statistics_mode.h"
#include "stdscr_window.h"
#include "utils.h"
#include "window.h"

struct PDTT {
  using dictionary_t = Dictionary;

  PDTT();

  auto run() -> void;

 private:
  dictionary_t dict_;
  Window window_;
};

#endif  // PDTT_PDTT_HH_
