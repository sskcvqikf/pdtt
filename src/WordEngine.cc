#include "WordEngine.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

std::ifstream HandledOpen(const std::string& filename) {
  std::ifstream fin(filename.c_str());
  if (!fin.is_open()) {
    std::cerr << "Something wrong with opening '" << filename
              << "'. Exiting...\n";
    std::terminate();
  }
  return fin;
}

size_t CountLines(std::ifstream& fin) {
  auto pos = fin.tellg();
  auto ret = std::count(std::istreambuf_iterator<char>(fin),
                        std::istreambuf_iterator<char>(), '\n');
  fin.clear();
  fin.seekg(pos);
  return ret;
}

WordEngine::WordEngine(const std::string& filename) {
  auto fin = HandledOpen(filename);
  auto lines = CountLines(fin);

  std::generate_n(std::back_inserter(store_), lines, [&fin] {
    std::string str;
    std::getline(fin, str);
    return str;
  });

  fin.close();
}

WordEngine::store_t WordEngine::Get(int n) const {
  std::vector<std::string> ret;
  std::sample(store_.cbegin(), store_.cend(), std::back_inserter(ret), n,
              std::mt19937{std::random_device{}()});
  return ret;
}
