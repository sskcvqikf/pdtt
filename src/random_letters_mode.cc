#include "random_letters_mode.h"

RandomLettersMode::RandomLettersMode() noexcept : Mode() {
  winptr_ = window().get_window();
  all_ = 0;
  correct_ = 0;
}

auto RandomLettersMode::destroy() const noexcept -> void {}

auto RandomLettersMode::get_letters() -> std::vector<char> {
  int my, mx;
  auto winptr = window().get_window();
  getmaxyx(winptr, my, mx);
  int nletters;
  curs_set(1);
  mvwprintw(winptr, my / 2, (mx - 22) / 2, "%s", "Enter amount of letters: ");
  echo();
  wscanw(winptr, "%d", &nletters);
  all_ = nletters;
  noecho();
  wclear(winptr);

  curs_set(0);
  srand(time(0));
  auto get_char = []() { return 'a' + rand() % 26; };
  std::vector<char> result(nletters);
  std::generate(result.begin(), result.end(), get_char);
  return result;
}

auto RandomLettersMode::preprocess() -> std::vector<char> {
  return get_letters();
}

auto RandomLettersMode::loop(const char i) -> void {
  int my, mx;
  getmaxyx(winptr_, my, mx);
  mvwaddch(winptr_, my / 2, mx / 2, i);
  auto g = wgetch(winptr_);
  if (i == g) correct_ += 1;
}

auto RandomLettersMode::postprocess(
    std::chrono::duration<long, std::ratio<1, 1000000000>> duration)
    const noexcept -> Stats {
  return Stats{all_, correct_, duration};
}
