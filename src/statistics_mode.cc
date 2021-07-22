#include "statistics_mode.hh"

StatisticsMode::StatisticsMode(std::string format, Stats stat)
    : format_(std::move(format)), window_(Window::create_fullscreen()), stat_(stat)
{
    wrefresh(window_.get_window());
}

StatisticsMode::~StatisticsMode()
{
    wclear(window_.get_window());
    wrefresh(window_.get_window());
    delwin(window_.get_window());
}

auto StatisticsMode::verbose() const
    -> void
{
    int my, mx;
    auto winptr = window_.get_window();
    curs_set(0);
    getmaxyx(winptr, my, mx);
    std::stringstream ss;
    ss << "A: " << stat_.all
       << " C: " << stat_.correct
       << " %: "
       << static_cast<double>(stat_.correct) / stat_.all * 100
       << "% T: "
       << static_cast<double>(stat_.ms.count()) / 1e9
       << 's';

    mvwprintw(winptr, my / 2, (mx - ss.str().length()) / 2, 
              "%s", ss.str().c_str());
    int move;
    for(;;)
    {
        move = wgetch(winptr);
        if (move == 'q')
            return;
    }
}
