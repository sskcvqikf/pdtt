#ifndef PDTT_WINDOW_HH_
#define PDTT_WINDOW_HH_

#include <memory>

#include <ncurses.h>

struct Window
{
    using window_t = WINDOW;
    using window_p = window_t *;

    Window(int h, int w, int y, int x);
    ~Window();

    static auto create_fullscreen()
        -> Window;

    auto get_window() const noexcept
        -> window_p;

private:
    int h_;
    int w_;
    int y_;
    int x_;
    
    window_p window_;
};

#endif // PDTT_WINDOW_HH_
