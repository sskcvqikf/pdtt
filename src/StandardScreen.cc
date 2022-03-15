#include "StandardScreen.h"

void StandardScreen::init() {
  window_ = initscr();
  cbreak();
  noecho();
  start_color();
  keypad(window_, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  curs_set(1);
}

StandardScreen::~StandardScreen() {
  curs_set(2);
  endwin();
}

StandardScreen StandardScreen::single_instance;

void StandardScreen::StartNcursesMode() { single_instance.init(); }

StandardScreen& StandardScreen::instance() { return single_instance; }

StandardScreen::window_t& StandardScreen::window() const noexcept {
  return *window_;
}

StandardScreen::window_t* GetWindow() {
  return &StandardScreen::instance().window();
}
