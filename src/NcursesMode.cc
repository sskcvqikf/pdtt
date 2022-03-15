#include "NcursesMode.h"

WINDOW* NCursesMode::window_ = nullptr;

void NCursesMode::Start() {
  window_ = initscr();
  cbreak();
  noecho();
  start_color();
  keypad(window_, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  curs_set(2);
}

void NCursesMode::Stop() {
  curs_set(2);
  endwin();
  window_ = nullptr;
}

WINDOW* NCursesMode::GetWindow() { return window_; }
