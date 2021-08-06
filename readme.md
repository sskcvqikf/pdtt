# PDTT
Poorly designed type tester.
#### Description:
A small piece of software that allows you to test out your skills in typing.
#### Build:
First things first. In `config.hh` you must define path to directory where to find words to train.
Then you can compile everything with 
```console
: make
```
#### Run:
In order to make it work you have to put a file called `default.txt` in the directory you specified earlier. The file is read line-by-line, so it is expected to be a single word in one line. Then simply run executable `main` in the `./build` directory.
Where to get words? I can recommend this https://github.com/first20hours/google-10000-english.
Also I have no clue if this works in other languages.
#### Usage:
There are two modes. First mode is just a mode where you type single words from `default.txt`. Second mode just shows you random letters you have to type. 
In menu navigate with `j` and `k` keys, Vim-like. Press `q` to quit (in afterstats it works also). There is no way to quit type mode.
