#include <ncurses.h>

#include "Interactor.h"
#include "Trainer.h"

int main() {
  WordEngine word_engine("default.txt");
  Trainer trainer(std::move(word_engine));
  trainer.Run({50});

  return 0;
}
