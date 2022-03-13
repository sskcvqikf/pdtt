#ifndef PDTT_RANDOM_LETTERS_MODE_HH_
#define PDTT_RANDOM_LETTERS_MODE_HH_

#include <algorithm>
#include <random>

#include "mode.h"
#include "stdscr_window.h"

struct RandomLettersMode : public Mode<RandomLettersMode> {
  using Mode::Mode;

  RandomLettersMode() noexcept;

  auto destroy() const noexcept -> void;

  auto preprocess() -> std::vector<char>;

  auto loop(const char i) -> void;

  auto postprocess(std::chrono::duration<long, std::ratio<1, 1000000000>>)
      const noexcept -> Stats;

 private:
  auto get_letters() -> std::vector<char>;

  WINDOW* winptr_;
  int all_;
  int correct_;
};

#endif  // PDTT_RANDOM_LETTERS_MODE_HH_
