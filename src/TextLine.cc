#include "TextLine.h"

#include <algorithm>

#include "NcursesMode.h"

Position GetTerminalSize(WINDOW* window) {
  Position ret;
  getmaxyx(window, ret.y, ret.x);
  return ret;
}

void PrintStringAt(const std::string& str, Position pos) {
  mvwprintw(NCursesMode::GetWindow(), pos.y, pos.x, "%s", str.c_str());
}

TextLine::TextLine(StringsIterator beg, StringsIterator end)
    : beg_(beg), end_(end), current_(beg_) {
  max_cols_ =
      std::max_element(beg_, end_, [](const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
      })->size();
  max_rows_ = 3;
}

std::pair<StringsIterator, StringsIterator>
TextLine::GetBeginAndEndOfStringsToShow() {
  StringsIterator beg;
  StringsIterator end;
  if (current_ == beg_) {
    beg = current_;
    end = current_ + 2;
  } else {
    beg = current_ - 1;
    end = current_ + 2;
  }
  return {beg, end};
}

Position TextLine::GetStartingPositionOfStringToBePrintedOn() {
  Position ret;
  auto max = GetTerminalSize(NCursesMode::GetWindow());
  if (current_ == beg_) {
    ret = {(max.x - max_cols_) / 2, (max.y - max_rows_) / 2 + 1};
  } else {
    ret = {(max.x - max_cols_) / 2, (max.y - max_rows_) / 2};
  }
  return ret;
}

void TextLine::UpdateCurrentPosition(Position pos) {
  if (current_ == beg_) {
    current_cursor_position_ = pos;
  } else {
    current_cursor_position_ = pos;
    ++current_cursor_position_.y;
  }
}

void TextLine::RedrawLine() {
  auto window = NCursesMode::GetWindow();
  wclear(window);
  auto [beg, end] = GetBeginAndEndOfStringsToShow();
  auto start = GetStartingPositionOfStringToBePrintedOn();

  for (int padding = 0; beg != end and beg != end_; ++padding, ++beg) {
    PrintStringAt(*beg, {start.x, start.y + padding});
  }

  UpdateCurrentPosition(start);
  MoveCursor();
}

void TextLine::SetCharUnderCursor(int ch) {
  mvwaddch(NCursesMode::GetWindow(), current_cursor_position_.y,
           current_cursor_position_.x, ch);
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
  wmove(NCursesMode::GetWindow(), current_cursor_position_.y,
        current_cursor_position_.x);
  Refresh();
}

void TextLine::Refresh() { wrefresh(NCursesMode::GetWindow()); }
