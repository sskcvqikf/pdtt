#include "window.h"

Window::Window(int h, int w, int y, int x)
    : h_(h), w_(w), y_(y), x_(x), window_(newwin(h_, w_, y_, x_)) {}

auto Window::create_fullscreen() -> Window { return Window(0, 0, 0, 0); }

auto Window::get_window() const noexcept -> Window::window_p { return window_; }

Window::~Window() { delwin(window_); }
