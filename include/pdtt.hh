#ifndef PDTT_PDTT_HH_
#define PDTT_PDTT_HH_

#include <string_view>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "dictionary.hh"
#include "default_mode.hh"
#include "random_letters_mode.hh"
#include "statistics_mode.hh"
#include "stdscr_window.hh"
#include "window.hh"
#include "utils.hh"


struct PDTT
{
    using dictionary_t = Dictionary;

    PDTT();

    auto run()
        -> void;

private:
    dictionary_t dict_;
    Window window_;

};

#endif // PDTT_PDTT_HH_
