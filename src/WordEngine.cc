#include "WordEngine.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

std::ifstream handled_open(const std::string& filename) {
  std::ifstream fin(filename.c_str());
  if (!fin.is_open()) {
    std::cerr << "Something wrong with opening '" << filename
              << "'. Exiting...\n";
    std::terminate();
  }
  return fin;
}

size_t count_lines(std::ifstream& fin) {
  auto pos = fin.tellg();
  auto ret = std::count(std::istreambuf_iterator<char>(fin),
                        std::istreambuf_iterator<char>(), '\n');
  fin.clear();
  fin.seekg(pos);
  return ret;
}

WordEngine::WordEngine(const std::string& filename) {
  auto fin = handled_open(filename);
  auto lines = count_lines(fin);

  std::generate_n(std::back_inserter(store_), lines, [&fin] {
    std::string str;
    std::getline(fin, str);
    return str;
  });

  fin.close();
}

std::vector<std::string> WordEngine::get(int n) const {
  std::vector<std::string> ret;
  std::sample(store_.cbegin(), store_.cend(), std::back_inserter(ret), n,
              std::mt19937{std::random_device{}()});
  return ret;
}
