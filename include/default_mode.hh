#ifndef PDTT_DEFAULT_MODE_HH_
#define PDTT_DEFAULT_MODE_HH_

#include <type_traits>

#include "mode.hh"
#include "stdscr_window.hh"

struct DefaultMode final : public Mode<DefaultMode> 
{
    using Mode::Mode;

    DefaultMode(Dictionary& dict) noexcept;

    auto destroy() const noexcept
        -> void;

    auto preprocess()
        -> std::vector<std::string>;

    auto postprocess(std::chrono::duration<long,
            std::ratio<1, 1000000000>>) const noexcept
        -> Stats;

    auto loop(std::string_view s)
        -> void;

    auto get_dict()
        -> Dictionary;

    private:
    auto get_train(std::vector<std::string> &) const
        -> std::vector<std::string>;

    Dictionary& dict_;
    WINDOW* winptr_;
    int all_;
    int correct_;
};

#endif // PDTT_DEFAULT_MODE_HH_
