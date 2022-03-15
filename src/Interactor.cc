#include "Interactor.h"

#include <algorithm>

#include "Position.h"
#include "StandardScreen.h"

int ReadChar() { return getch(); }

std::optional<Interactor> Interactor::Create(Strings strings) {
  if (strings.empty()) {
    return {};
  }
  for (const auto& str : strings) {
    if (str.empty()) return {};
  }
  return Interactor(std::move(strings));
}

Interactor::Interactor(Strings strings)
    : strings_(std::move(strings)),
      text_line_(strings_.cbegin(), strings_.cend()) {
  iterators_.vec_i = strings_.cbegin();
  iterators_.str_i = iterators_.vec_i->cbegin();

  text_line_.RedrawLine();
}

int Interactor::GetInputChar() const { return ReadChar(); }

int Interactor::GetCurrentChar() { return *iterators_.str_i; }

void Interactor::SetCurrentChar(int ch) { text_line_.SetCharUnderCursor(ch); }

bool Interactor::MoveForward() { return IncrementStrI(); }

bool Interactor::MoveBackward() { return DecrementStrI(); }

bool Interactor::IncrementStrI() {
  if (iterators_.str_i == iterators_.vec_i->cend()) {
    if (!IncrementVecI()) return false;
    iterators_.str_i = iterators_.vec_i->cbegin();
  } else {
    ++iterators_.str_i;
    text_line_.MoveCursorRightBy(1);
  }
  return true;
}

bool Interactor::DecrementStrI() {
  if (iterators_.str_i == iterators_.vec_i->cbegin()) {
    if (!DecrementVecI()) return false;
    iterators_.str_i = iterators_.vec_i->cend() - 1;
  } else {
    --iterators_.str_i;
    text_line_.MoveCursorLeftBy(1);
  }
  return true;
}

bool Interactor::IncrementVecI() {
  if (iterators_.vec_i == strings_.cend()) return false;
  ++iterators_.vec_i;
  text_line_.IncrementLine();
  text_line_.RedrawLine();
  return true;
}

bool Interactor::DecrementVecI() {
  if (iterators_.vec_i == strings_.cbegin()) return false;
  --iterators_.vec_i;
  text_line_.DecrementLine();
  text_line_.RedrawLine();
  text_line_.MoveCursorRightBy(iterators_.vec_i->size() - 1);
  return true;
}
