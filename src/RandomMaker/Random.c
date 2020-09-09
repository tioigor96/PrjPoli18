//
// Created by igor on 02/03/18.
//

#include "../../lib/RandomMaker/Random.h"

int __RNDFD = -1;

int openRandom() {

    if (__RNDFD == -1)
        __RNDFD = open("/dev/urandom", O_RDONLY);

    if (__RNDFD < 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

struct RndRes urnd() {

    int res;
    __uint32_t buff;
    res = read(__RNDFD, &buff, sizeof(4));
    if (res < 0) {
        struct RndRes t = {-1, EXIT_FAILURE};
        return t;
    } else {
        struct RndRes t = {buff, EXIT_SUCCESS};
        return t;
    }

}

int closeRandom() {
    if (close(__RNDFD) < 0) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}