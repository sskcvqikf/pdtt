#include "Trainer.h"

#include <ncurses.h>

#include <numeric>

#include "Interactor.h"

constexpr int kMaxLength = 50;

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
  auto train_selection = word_engine_.get(train_parameters.n_words);

  Strings strings = GetStrings(train_selection);

  auto interator = Interactor::Create(std::move(strings));
  if (!interator) {
    return;
  }

  for (;;) {
    auto input_char = interator->GetInputChar();
    if (input_char == '\n') {
      break;
    }
    if (input_char == KEY_BACKSPACE || input_char == KEY_DC ||
        input_char == 127) {
      interator->MoveBackward();
      auto char_to_restore = interator->GetCurrentChar();
      interator->SetCurrentChar(char_to_restore);
      continue;
    }

    auto current_char = interator->GetCurrentChar();
    if (current_char != input_char) {
      interator->SetCurrentChar(current_char | A_BOLD | COLOR_PAIR(1));
    }

    if (!interator->MoveForward()) {
      break;
    }
  }
}
