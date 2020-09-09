//
// Created by igor on 02/03/18.
//

#ifndef PRJPOLI18_RANDOM_H
#define PRJPOLI18_RANDOM_H

#include <stdio.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * File Descriptor for RandomGen to "/dev/random"
 */
extern int __RNDFD;

struct RndRes {
    __uint32_t res;
    int exit_status;
};

/**
 * Initialize __RNDFD for utilize the random file on *unix OS.
 * return EXIT_FAILURE status if errors, else EXIT_SUCCESS.
 */
int openRandom();


/**
 * Close __RNDFD. After closing file
 * @return
 */
int closeRandom();

/**
 * Return an unsigned int 32bit, couple to exit_status.
 * @return struct RndRes {__uint32_t res, int exit_status}
 */
struct RndRes urnd();

#endif //PRJPOLI18_RANDOM_H
