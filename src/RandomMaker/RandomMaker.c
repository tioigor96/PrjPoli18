//
// Created by igor on 02/03/18.
//

#include "../../lib/RandomMaker/RandomMaker.h"
#include "../../lib/RandomMaker/Random.h"

char *randomWordMaker(__uint32_t len) {

    openRandom();

    char *word = calloc(sizeof(char), len);
    for (__uint32_t i = 0; i < len; i++) {
        word[i] = (urnd().res % 26) + 'a';

    }
    return word;
}