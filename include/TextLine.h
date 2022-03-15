#ifndef PDTT_TEXTLINE_H_
#define PDTT_TEXTLINE_H_
#pragma once

#include <string>
#include <vector>

#include "Position.h"

using Strings = std::vector<std::string>;
using StringsIterator = std::vector<std::string>::const_iterator;

class TextLine {
 public:
  TextLine(StringsIterator beg, StringsIterator end);

  void RedrawLine();

  void IncrementLine();
  void DecrementLine();

  void MoveCursorRightBy(int n);
  void MoveCursorLeftBy(int n);

  void SetCharUnderCursor(int ch);

 private:
  void MoveCursor();
  void Refresh();

  std::pair<StringsIterator, StringsIterator> GetBeginAndEndOfStringsToShow();
  Position GetStartingPositionOfStringToBePrintedOn();
  void UpdateCurrentPosition(Position pos);

 private:
  StringsIterator beg_;
  StringsIterator end_;
  StringsIterator current_;
  Position current_cursor_position_;
  int max_cols_;
  int max_rows_;
};

#endif  // PDTT_TEXTLINE_H_
