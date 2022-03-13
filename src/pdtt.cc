#include "pdtt.h"

PDTT::PDTT() : dict_(), window_(Window::create_fullscreen()) {
  wrefresh(window_.get_window());
}

auto PDTT::run() -> void {
  std::unordered_map<int, std::string> choices{
      {1, "Default Mode"},
      {2, "Random letters Mode"},
  };
  auto max_len =
      std::max_element(choices.cbegin(), choices.cend(), [](auto i1, auto i2) {
        return i1.second.length() < i2.second.length();
      })->second.length();
  int all = choices.size(), curr = all;

  int my, mx;
  auto winptr = window_.get_window();
  curs_set(0);
  getmaxyx(winptr, my, mx);

  auto print_menu = [&choices, winptr, &curr, &my, &mx, &all]() {
    for (const auto& c : choices) {
      auto& cs = c.second;
      mvwprintw(winptr, (my - all) / 2 + curr, (mx - cs.length()) / 2, "%s",
                cs.c_str());
      curr -= 1;
    }
  };
  print_menu();

  auto update = [&winptr, &all, &max_len, &my, &mx, &curr](attr_t attr) {
    mvwchgat(winptr, (my - all) / 2 + curr, (mx - max_len) / 2, max_len, attr,
             0, NULL);
  };

  auto incr = [&curr](int min, int max) {
    if (curr == max)
      curr = min;
    else
      ++curr;
  };

  auto decr = [&curr](int min, int max) {
    if (curr == min)
      curr = max;
    else
      --curr;
  };

  curr += 1;
  update(A_BLINK);

  int next_move;
  Stats stat;
  for (;;) {
    next_move = wgetch(window_.get_window());
    switch (next_move) {
      case 'j':
        update(A_NORMAL);
        incr(1, all);
        update(A_BLINK);
        break;

      case 'k':
        update(A_NORMAL);
        decr(1, all);
        update(A_BLINK);
        break;

      case 'q':
        delwin(winptr);
        return;

      case '\n':
        switch (curr) {
          case 1:
            stat = DefaultMode(dict_).run();
            break;
          case 2:
            stat = RandomLettersMode().run();
            break;
        }
        StatisticsMode("", stat).verbose();
        curr = all;
        print_menu();
        curr += 1;
        update(A_BLINK);
    }
  }
}
