#ifndef PDTT_INTERACTOR_H_
#define PDTT_INTERACTOR_H_
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "TextLine.h"

using Strings = std::vector<std::string>;
using StringsIterator = std::vector<std::string>::const_iterator;

class Interactor final {
 public:
  static std::optional<Interactor> Create(Strings strings);

 public:
  int GetInputChar() const;
  int GetCurrentChar();

  void SetCurrentChar(int ch);

  bool MoveForward();
  bool MoveBackward();

 private:
  Interactor(Strings strings);

  struct Iterators {
    std::vector<std::string>::const_iterator vec_i;
    std::string::const_iterator str_i;
  } iterators_;

  bool IncrementVecI();
  bool IncrementStrI();

  bool DecrementVecI();
  bool DecrementStrI();

  Strings strings_;
  TextLine text_line_;
};

#endif  // PDTT_INTERACTOR_H_
