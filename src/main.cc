#include <iostream>

#include "Arguments.h"
#include "Interactor.h"
#include "NcursesMode.h"
#include "Trainer.h"

struct AppParameters {
  std::string filename;
  TrainParameters train_parameters;
};

void StartApp(AppParameters params) {
  NCursesMode::Start();
  WordEngine word_engine(params.filename);
  Trainer trainer(std::move(word_engine));
  trainer.Run(params.train_parameters);

  NCursesMode::Stop();
}

int main(int argc, char** argv) {
  Arguments args(argc, argv);

  auto is_help = args.is_help();
  if (is_help) {
    std::cout << args.GetHelp();
    return 0;
  }

  auto filename = args.file_path();
  if (!filename) {
    std::cout << "You have to provide filename.\n -h to help.\n";
    return 1;
  }

  auto n_words = args.n_words();
  if (!n_words) {
    std::cout
        << "You have to provide number of words to train on.\n -h to help.\n";
    return 1;
  }

  StartApp(AppParameters{std::move(*filename), {*n_words}});

  return 0;
}
