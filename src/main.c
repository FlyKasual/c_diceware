#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include "dicewareList.h"

#define MAXIMUM_SIZE 1024

static void generateDicewarePassword(const unsigned int numberOfWords, const char separator, char *const target);

int main(int argc, char **argv) {
    unsigned int numberOfWords = 4;
    unsigned int numberOfPasswordsToCreate = 4;
    char separator = '-';
    int flag = 0;
    char password[MAXIMUM_SIZE] = "";

    // TODO: Implement a help notice
    while ((flag = getopt(argc, argv, "n:w:s:")) != -1) {
        switch (flag) {
            case 'w':
                numberOfWords = strtoul(optarg, NULL, 10);
                break;
            case 'n':
                numberOfPasswordsToCreate = strtoul(optarg, NULL, 10);
                break;
            case 's':
                separator = *optarg;
                break;
        }
    }

    printf(
        "Generating %u passwords, each using %u words and the separator '%c'.\nEach password will have an entropy of around %.02f bits.\n\n",
        numberOfPasswordsToCreate,
        numberOfWords,
        separator,
        12.9 * numberOfWords
    );

    for (unsigned int i = 0; i < numberOfPasswordsToCreate; ++i) {
        memset(password, '\0', MAXIMUM_SIZE);
        generateDicewarePassword(numberOfWords, separator, password);
        printf("%s\n", password);
    }


    return EXIT_SUCCESS;
}

static void generateDicewarePassword(const unsigned int numberOfWords, const char separator, char *const target) {
    FILE *random = fopen("/dev/random", "r");
    // TODO: Error handling if fopen failed.
    // TODO: Using /dev/random is not very portable
    for (unsigned int i = 0; i < numberOfWords; ++i) {
        unsigned int key = 0;
        for (unsigned int j = 0; j < 5; ++j) {
            unsigned int read = 0;
            fread(&read, sizeof(unsigned int), 1, random);
            key += read % 6 * pow(6, j);
        }
        if (strlen(target) + strlen(dicewareList[key]) <= MAXIMUM_SIZE) {
            strcat(target, dicewareList[key]);
            if (i < numberOfWords - 1 && strlen(target) + 1 < MAXIMUM_SIZE) {
                target[strlen(target)] = separator;
            } else {
                fclose(random);
                random = NULL;
                return;
            }
        }
    }
    fclose(random);
    random = NULL;
}
