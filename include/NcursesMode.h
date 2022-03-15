#ifndef PDTT_NCURSESMODE_H_
#define PDTT_NCURSESMODE_H_
#pragma once

#include <ncurses.h>

class NCursesMode {
 public:
  static void Start();
  static void Stop();

  static WINDOW* GetWindow();

 private:
  static WINDOW* window_;
};

#endif  // PDTT_NCURSESMODE_H_
