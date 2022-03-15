#include "TextLine.h"

#include <algorithm>

#include "StandardScreen.h"

Position GetTerminalSize(StandardScreen::window_t* window) {
  Position ret;
  getmaxyx(window, ret.y, ret.x);
  return ret;
}

void PrintStringAt(const std::string& str, Position pos) {
  mvwprintw(GetWindow(), pos.y, pos.x, "%s", str.c_str());
}

TextLine::TextLine(StringsIterator beg, StringsIterator end)
    : beg_(beg), end_(end), current_(beg_) {
  max_cols = std::max_element(beg_, end_, [](const auto& lhs, const auto& rhs) {
               return lhs.size() < rhs.size();
             })->size();
  max_rows = 3;
}

void TextLine::RedrawLine() {
  auto window = GetWindow();
  wclear(window);
  auto max = GetTerminalSize(window);
  StringsIterator beg;
  StringsIterator end;
  Position start;
  if (current_ == beg_) {
    start = {(max.x - max_cols) / 2, (max.y - max_rows) / 2 + 1};
    beg = current_;
    end = current_ + 2;
    current_cursor_position_ = start;
  } else {
    start = {(max.x - max_cols) / 2, (max.y - max_rows) / 2};
    beg = current_ - 1;
    end = current_ + 2;
    current_cursor_position_ = start;
    ++current_cursor_position_.y;
  }

  for (int padding = 0; beg != end and beg != end_; ++padding, ++beg) {
    PrintStringAt(*beg, {start.x, start.y + padding});
  }
  MoveCursor();
}

void TextLine::SetCharUnderCursor(int ch) {
  mvwaddch(GetWindow(), current_cursor_position_.y, current_cursor_position_.x,
           ch);
  MoveCursor();
}

void TextLine::IncrementLine() {
  if (current_ != (end_ - 1)) ++current_;
}

void TextLine::DecrementLine() {
  if (current_ != beg_) --current_;
}

void TextLine::MoveCursorRightBy(int n) {
  current_cursor_position_.x += n;
  MoveCursor();
}

void TextLine::MoveCursorLeftBy(int n) {
  current_cursor_position_.x -= n;
  MoveCursor();
}

void TextLine::MoveCursor() {
  wmove(GetWindow(), current_cursor_position_.y, current_cursor_position_.x);
  Refresh();
}

void TextLine::Refresh() { wrefresh(GetWindow()); }
