#ifndef PDTT_MODE_HH_
#define PDTT_MODE_HH_

#include <type_traits>

#include "dictionary.hh"
#include "window.hh"
#include "utils.hh"

template<typename Derived>
struct Mode
{
    Mode();

    ~Mode();

    auto run()
        -> Stats;

    auto window() const noexcept
        -> const Window &;
    
private:
    Window window_;
};

template<typename Derived>
Mode<Derived>::Mode()
    : window_(Window::create_fullscreen())
{
    wrefresh(window().get_window());
}

template<typename Derived>
auto Mode<Derived>::run()
    -> Stats
{
    auto dthis = static_cast<Derived *>(this);
    auto train = dthis->preprocess();
    auto start = std::chrono::high_resolution_clock::now();
    for(const auto& i: train){
        dthis->loop(i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast
                        <std::chrono::nanoseconds>
                        (stop - start);
    auto result = dthis->postprocess(duration);
    return result;
    
}

template<typename Derived>
auto Mode<Derived>::window() const noexcept
    -> const Window &
{
    return window_;
}

template<typename Derived>
Mode<Derived>::~Mode()
{
    static_cast<Derived *>(this)->destroy();
    wclear(window_.get_window());
    wrefresh(window_.get_window());
    delwin(window_.get_window());
}
#endif // PDTT_MODE_HH_
