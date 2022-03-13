#include "dictionary.h"

Dictionary::Dictionary() {
  namespace fs = std::filesystem;
  fs::directory_iterator directory;
  try {
    directory = fs::directory_iterator(config::DICTIONARY_DIR);
  } catch (fs::filesystem_error &e) {
    std::cerr << "Cannot open directory with dictionaries. Exiting...\n";
    exit(1);
  }
  for (const auto &fp : directory) {
    if (fp.is_regular_file()) {
      auto fn = fp.path().filename().native();
      std::ifstream fin(fp.path().c_str());
      if (!fin.is_open()) {
        std::cerr << "Something wrong with opening '" << fn
                  << "'. Exiting...\n";
      }
      auto loc = static_cast<unsigned long>(
          std::count(std::istreambuf_iterator<char>(fin),
                     std::istreambuf_iterator<char>(), '\n'));
      substore_t vw{loc};
      std::string line;
      fin.clear();
      fin.seekg(0);
      std::for_each(vw.begin(), vw.end(),
                    [&fin](std::string &v) { std::getline(fin, v); });
      fin.close();
      store_[fn] = vw;
    }
  }
  if (store_.find("default.txt") == store_.end()) {
    std::cerr << "You should put file called 'default.txt' in dictionary "
                 "directory. Exiting...\n";
    exit(1);
  }
}

auto Dictionary::store() const noexcept -> const Dictionary::store_t & {
  return store_;
}
