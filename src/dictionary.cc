#include "dictionary.hh"

Dictionary::Dictionary()
{
    namespace fs = std::filesystem;
    for (const auto &fp: fs::directory_iterator(config::DICTIONARY_DIR)){
        if (fp.is_regular_file()) 
        {
            auto fn = fp.path().filename().native();
            std::ifstream fin(fp.path().c_str());
            if (!fin.is_open())
            {
                // TODO
            }
            auto loc = static_cast<unsigned long>(std::count(
                    std::istreambuf_iterator<char>(fin),
                    std::istreambuf_iterator<char>(),
                    '\n'
                ));
            substore_t vw {loc};
            std::string line;
            fin.clear();
            fin.seekg(0);
            std::for_each(vw.begin(), vw.end(),
                          [&fin](std::string &v){
                              std::getline(fin, v);
                          });
            fin.close();
            store_[fn] = vw;
        }
    }
}

auto Dictionary::store() const noexcept
    -> const Dictionary::store_t &
{
    return store_;
}
