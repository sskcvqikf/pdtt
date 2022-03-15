# PDTT
Poorly designed type tester.
#### Description:
A small piece of software that allows you to test your skills in typing.
#### Build:
```console
: cmake -S. -Bbuild
: cd build
: make
```
#### Run:
The executable supports two command line arguments: filename and number of words to display. Both must be provided. So, use aliases in order to simplify your life. Help is also supported.

```
  -h, --help                  Show this message.
  -f, --filename <filename>   Path to file with words.
                              Words in file must be splitted by newlines.
                              Go get one from https://github.com/first20hours/google-10000-english.
  -n, --nwords <N>            Count of words to show. Taken words are shuffled.
```
