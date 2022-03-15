#include "Trainer.h"

#include <ncurses.h>

#include <numeric>

#include "Interactor.h"

constexpr int kMaxLength = 50;

bool IsBackspace(int ch) {
  return ch == KEY_BACKSPACE or ch == KEY_DC or ch == 127;
}

bool IsEnter(int ch) { return ch == '\n'; }

Strings GetStrings(const std::vector<std::string>& train_selection) {
  Strings ret;

  size_t capacity = kMaxLength;
  std::string buf;

  for (const auto& i : train_selection) {
    if (capacity < i.size()) {
      buf.pop_back();
      ret.push_back(std::move(buf));
      std::string().swap(buf);  // reinit
      capacity = kMaxLength;
    }
    buf += i + " ";
    capacity -= i.size();
  }
  return ret;
}

Trainer::Trainer(WordEngine word_engine)
    : word_engine_(std::move(word_engine)) {}

void Trainer::Run(TrainParameters train_parameters) const {
  auto train_selection = word_engine_.Get(train_parameters.n_words);

  Strings strings = GetStrings(train_selection);

  auto interator = Interactor::Create(std::move(strings));
  if (!interator) {
    return;
  }

  for (;;) {
    auto input_char = interator->GetInputChar();
    if (IsEnter(input_char)) {
      break;
    }
    if (IsBackspace(input_char)) {
      interator->MoveBackward();
      interator->MarkCorrect();
      continue;
    }

    auto current_char = interator->GetCurrentChar();
    if (current_char != input_char) {
      interator->MarkUncorrect();
    }

    if (!interator->MoveForward()) {
      break;
    }
  }
}
