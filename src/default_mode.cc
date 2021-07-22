#include "default_mode.hh"

auto DefaultMode::get_train(std::vector<std::string>& vec) const
    -> std::vector<std::string>
{
    int my, mx;
    auto winptr = window().get_window();
    getmaxyx(winptr, my, mx);
    int nwords;
    curs_set(1);
    mvwprintw(winptr,
              my / 2,
              (mx - 22) / 2,
              "%s",
              "Enter amount of words: ");
    echo();
    wscanw(winptr, "%d", &nwords);
    noecho();
    wclear(winptr);
    std::stringstream ss;
    int len = 0;
    std::vector<std::string> samples;
    std::sample(vec.cbegin(), vec.cend(),
            std::back_inserter(samples), nwords,
            std::mt19937{std::random_device{}()});
    std::vector<std::string> train;

    for(const auto& s: samples) 
    {   
        if (len == 0){
            len = s.length() % 3 + 1;
            train.push_back(ss.str());
            ss.str("");
        }
        else
            ss << " ";
        ss << s;
        --len;
    }
    if (ss.str() != "")
        train.push_back(ss.str());
    return train;
}

DefaultMode::DefaultMode(Dictionary &dict) noexcept
    : Mode(), dict_(dict)
{
    all_ = 0;
    correct_ = 0;
    winptr_ = window().get_window();
}

auto DefaultMode::preprocess()
    -> std::vector<std::string>
{
    auto vec = dict_.store().at("default.txt");
    return get_train(vec);
}

auto DefaultMode::loop(std::string_view w)
    -> void
{
    int my, mx;
    getmaxyx(winptr_, my, mx);
    auto begx = (mx - w.length()) / 2;
    auto begy = my / 2;
    mvwprintw(winptr_, begy, begx, "%s", w.data());
    curs_set(1);
    for(const auto& s: w){
        wmove(winptr_, begy, begx);
        auto rs = wgetch(winptr_);
        if (s != rs)
            mvwaddch(winptr_, begy, begx,
                     rs|A_BOLD|COLOR_PAIR(1));
        else 
            ++correct_;
        ++all_;
        ++begx;
    }
    curs_set(0);
    wclear(winptr_);
}

auto DefaultMode::postprocess(std::chrono::duration<long,
            std::ratio<1, 1000000000>> duration) const noexcept
    -> Stats
{
    return Stats{all_, correct_, duration};
}

auto DefaultMode::destroy() const noexcept
    -> void
{}
