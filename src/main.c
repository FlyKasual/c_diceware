#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include "dicewareList.h"

#define MAXIMUM_SIZE 1024

static void generateDicewarePassword(unsigned int numberOfWords, char separator, char *const target);

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

    printf("Generating %u passwords, each using %u words and the separator '%c'\n\n", numberOfPasswordsToCreate, numberOfWords, separator);

    for (unsigned int i = 0; i < numberOfPasswordsToCreate; ++i) {
        memset(password, '\0', MAXIMUM_SIZE);
        generateDicewarePassword(numberOfWords, separator, password);
        printf("%s\n", password);
    }


    return EXIT_SUCCESS;
}

static void generateDicewarePassword(unsigned int numberOfWords, char separator, char *const target) {
    unsigned long key = 0;
    for (unsigned int i = 0; i < numberOfWords; ++i) {
        key = 0;
        for (unsigned int j = 0; j < 5; ++j) {
            key += rand() % 6 * pow(6, j); // TODO: Replace `rand` with a true random number generator
        }
        if (strlen(target) + strlen(dicewareList[key]) <= MAXIMUM_SIZE) {
            strcat(target, dicewareList[key]);
            if (i < numberOfWords - 1 && strlen(target) + 1 < MAXIMUM_SIZE) {
                target[strlen(target)] = separator;
            } else {
                return;
            }
        }
    }
}
