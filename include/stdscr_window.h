#ifndef PDTT_STDSCR_WINDOW_HH_
#define PDTT_STDSCR_WINDOW_HH_

#include <ncurses.h>

#include <memory>
#include <optional>

struct StdscrWindow final  // singleton
{
  using window_t = WINDOW;
  using window_p = window_t *;

  auto get_window() const noexcept -> window_p;

  static auto stdscrwindow() -> StdscrWindow *;

 private:
  StdscrWindow();
  ~StdscrWindow();

  static bool is_initialized_;
  static StdscrWindow instance_;

  window_p window_;
};

#endif  // PDTT_STDSCR_WINDOW_HH_
