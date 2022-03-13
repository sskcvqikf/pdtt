#include "stdscr_window.h"

bool StdscrWindow::is_initialized_;

StdscrWindow StdscrWindow::instance_;

StdscrWindow::StdscrWindow() : window_(initscr()) {
  is_initialized_ = true;
  raw();
  noecho();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
}

StdscrWindow::~StdscrWindow() {
  curs_set(2);
  endwin();
  is_initialized_ = false;
}

auto StdscrWindow::stdscrwindow() -> StdscrWindow* {
  return is_initialized_ ? &instance_ : nullptr;
}

auto StdscrWindow::get_window() const noexcept -> StdscrWindow::window_p {
  return window_;
}
