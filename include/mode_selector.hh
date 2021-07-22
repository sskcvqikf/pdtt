#ifndef PDTT_MODE_SELECTOR_HH_
#define PDTT_MODE_SELECTOR_HH_

#include "default_mode.hh"

template<int N>
struct ModeNumber;

template<>
struct ModeNumber<1>
{
    using SelectedMode = DefaultMode;
};
#endif // PDTT_MODE_SELECTOR_HH_
