#ifndef PDTT_WORDENGINE_H_
#define PDTT_WORDENGINE_H_
#pragma once

#include <string>
#include <vector>

class WordEngine final {
 public:
  using store_t = std::vector<std::string>;

  WordEngine(const std::string& filename);

  std::vector<std::string> get(int n) const;

 private:
  store_t store_;
};

#endif  // PDTT_WORDENGINE_H_
