#ifndef PDTT_STANDARDSCREEN_H_
#define PDTT_STANDARDSCREEN_H_
#pragma once

#include <ncurses.h>

#include <memory>
#include <optional>

class StandardScreen final {
 public:
  using window_t = WINDOW;

  StandardScreen(const StandardScreen&) = delete;
  StandardScreen(StandardScreen&&) = delete;
  StandardScreen& operator=(const StandardScreen&) = delete;
  StandardScreen& operator=(StandardScreen&&) = delete;

  window_t& window() const noexcept;

  static StandardScreen& instance();

 private:
  StandardScreen();
  ~StandardScreen();

  window_t* window_;

  static StandardScreen single_instance;
};

StandardScreen::window_t* GetWindow();

#endif  // PDTT_STANDARDSCREEN_H_
