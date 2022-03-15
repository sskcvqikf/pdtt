#include "Arguments.h"

Arguments::Arguments(int argc, char** argv) : parser_(argc, argv) {}

std::optional<int> Arguments::n_words() {
  return parser_.get<int>({"nwords", 'n'});
}

std::optional<std::string> Arguments::file_path() {
  return parser_.get<std::string>({"filename", 'f'});
}

bool Arguments::is_help() { return parser_.get<bool>({"help", 'h'}); }

std::string Arguments::GetHelp() {
  return "A tool used to practice your typing. Simple. No stats.\n"
         "  -h, --help                  Show this message.\n"
         "  -f, --filename <filename>   Path to file with words.\n"
         "                              Words in file must be splitted by "
         "newlines.\n"
         "                              Go get one from "
         "https://github.com/first20hours/google-10000-english.\n"
         "  -n, --nwords <N>            Count of words to show. Taken words "
         "are shuffled.\n";
}
