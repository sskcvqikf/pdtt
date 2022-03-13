#ifndef PDTT_DICTIONARY_
#define PDTT_DICTIONARY_

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "config.h"

struct Dictionary final {
  using substore_t = std::vector<std::string>;
  using store_t = std::unordered_map<std::string, substore_t>;

  Dictionary();

  auto store() const noexcept -> const store_t&;

 private:
  store_t store_;
};

#endif  // PDTT_DICTIONARY_
