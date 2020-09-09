//
// Created by igor on 17/10/18.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../lib/timing/Poli_prng.h"
#include "../../lib/prj/CLBST_s.h"
#include "../../lib/timing/timing.h"
#include "../../lib/prj/graph.h"


#ifndef  valgrind_compliant
#define valgrind_compliant
#endif

#ifndef tmp_file
#define tmp_file "/tmp/poli_XXXXXX"
#endif

#ifndef alpha
#define alpha "abcdefghijklmnopqrstuvwxyz"
#endif

#define MIN_SAMPLE 5
#define ZA 1.96
#define MAX_RELATIVE_DELTA 0.05

int char_compareTo(void *o1, void *o2) {
    char c1 = *((char *) o1);
    char c2 = *((char *) o2);

    if (c1 == c2) {
        return 0;
    } else if (c1 < c2) {
        return -1;
    } else {
        return 1;
    }
}

int hashFn(void *o) {
    return (*((char *) o)) - 'a';
}

size_t fieldSize(void *p) {
    return sizeof(char);
}

void printDot(VE *g) {
    printf("graph G {\n");
    for (VE *G = g; G; G = G->n) {
        printf("\t%c [label=\"%d\"]\n", *((char *) (G->v)), hashFn(((char *) G->v)));
        for (edge *es = G->es; es; es = es->n) {
            printf("\t%c -- %c\n", *((char *) G->v), *((char *) es->v));
        }
    }
    printf("}\n");
}

int main() {

    CLBST_root *cnt = NULL;
    VEdet *G = NULL;

    char *fname = malloc(strlen(tmp_file));
    strncpy(fname, tmp_file, strlen(tmp_file));
    int new_stdin = mkstemp(fname);
    dup2(new_stdin, STDIN_FILENO);

    int new_stdout = open("/dev/null", O_WRONLY);
    int realstdout = dup(STDOUT_FILENO);
    dup2(new_stdout, STDOUT_FILENO);


    void prepara(int len) {

        char c;
        //da spaccare le write?
        for (int i = 0; i < len; i++) {
            c = ((char) (rrandom() * 26 + 'a'));
            write(new_stdin, &c, 1);
        }

        lseek(new_stdin, 0, SEEK_SET);

    }

    void riavvolgi() {
#ifdef valgrind_compliant
//        CLBST_destroy(cnt);
//        destroy_VEdet(G);
#endif
        lseek(STDIN_FILENO, 0, SEEK_SET);
    }

    //CONTROLLO TEMPO INSERT CLBST
    void execute() {
        cnt = CLBST_init(strlen(alpha), hashFn, char_compareTo);
        unsigned long int *cards = calloc(strlen(alpha), sizeof(unsigned long int));
        char c;

        while ((c = getchar()) != EOF) {
            cards[c - alpha[0]]++;
            char *ct = calloc(1, sizeof(char));
            (*ct) = c;

#ifdef valgrind_compliant
            if (CLBST_insert(&cnt, ct) <= 0)
                free(ct);
#endif
        }
        unsigned long int min = cards[0];
        unsigned long int max = cards[0];

        for (int i = 1; i < strlen(alpha); i++) {
            min = cards[i] ? min < cards[i] && min ? min : cards[i] : min;
            max = cards[i] ? max > cards[i] && max ? max : cards[i] : max;
        }

        G = makeGraph(cnt, min, max, char_compareTo);
        printf("%lu %lu\n", G->v, G->e);
        printDot(G->g);
#ifdef valgrind_compliant
        destroy_VEdet(G);
        cnt = CLBST_destroy(cnt);
#endif
    }


    /*execute per CLBST normale*/
      /*void execute() {
        cnt = CLBST_init(strlen(alpha), hashFn, char_compareTo);
        char c;

        while ((c = getchar()) != EOF) {
            char *ct = calloc(1, sizeof(char));
            (*ct) = c;
            CLBST_insert(&cnt, ct);

        }
    }*/

    for (int i = 0; i < 30000; i += 1000) {
        result r = misurazione(i, MIN_SAMPLE, ZA, MAX_RELATIVE_DELTA, prepara, execute, riavvolgi);

        dprintf(realstdout, "%d\t%.60f\t%.60f\n", i, ((double) r.e / (double) CLOCKS_PER_SEC),
                ((double) r.delta / (double) CLOCKS_PER_SEC));
    }


    close(new_stdin);
    unlink(fname);

    return 0;
}
