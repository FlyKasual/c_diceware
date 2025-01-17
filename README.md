# C Diceware

This is a pet project of mine which I wrote mainly to learn a bit more C. It is a command line tool that generates
passwords using [diceware](https://en.wikipedia.org/wiki/Diceware).

## Compilation

In order to compile the source code, you can use `make` in conjunction with the makefile included in the project. That
makefile uses the `gcc` compiler. Of course, you are free to use any other method for compilation you like. Notice that
the project uses the `math` library, so you might have to manually link that if you do not use `make`.

## Usage

After compiling the project, you can just call the created binary on the command line. The program accepts three
optional flags:

| Flag | Effect | default |
| --- | --- | --- |
| n | Number of passwords to create | 4 |
| w | Number of words to use in each password | 4 |
| s | Character to be used to separate words in a password | '-' |

## Warning and disclaimer

As a warning: The program currently uses `/dev/random` to generate random bytes which is supposed to simulate rolling
of the dice. Firstly, that file might not exist on your system. In that case, the program will simply not work.
Secondly, and this is even more important: I do not know whether the bytes generated this way are truly random or
merely pseudorandom.

**There is absolutely no guarantee that the passwords created with this program are truly strong! Use at own risk!**

## License

This project is licensed under the [Apache-2.0 license](./LICENSE).
