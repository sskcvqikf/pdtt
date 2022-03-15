#ifndef PDTT_ARGUMENTS_H_
#define PDTT_ARGUMENTS_H_
#pragma once

#include "pd/pdargs.hh"

class Arguments {
 public:
  Arguments(int argc, char** argv);

  std::optional<int> n_words();
  std::optional<std::string> file_path();

  bool is_help();

  std::string GetHelp();

 private:
  pd::pdargs parser_;
};

#endif  // PDTT_ARGUMENTS_H_
