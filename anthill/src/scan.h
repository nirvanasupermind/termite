#include "defs.h"
#include "data.h"
#include "decl.h"
int next(void) {
    int c;
    if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
    }
    if (Mp) {
    if ('\0' == *Macp[Mp-1]) {
    Macp[Mp-1] = NULL;
    return Macc[--Mp];
    }
    else {
    return *Macp[Mp-1]++;
    }
    }
    c = fgetc(Infile);
    if ('\n' == c) Line++;
    return c;
    }


    void putback(int c) {
        Putback = c;
        }

        