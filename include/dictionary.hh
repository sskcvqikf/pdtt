#ifndef PDTT_DICTIONARY_
#define PDTT_DICTIONARY_

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <random>
#include <iostream>

#include "config.hh"


struct Dictionary final
{   
    using substore_t = std::vector<std::string>;
    using store_t = std::unordered_map<
        std::string,
        substore_t>; 
    
    Dictionary();

    auto store() const noexcept
        -> const store_t&;

private:
    store_t store_; 

};

#endif // PDTT_DICTIONARY_
