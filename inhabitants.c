#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "inhabitants.h"


bool goes_away(unsigned int *rng, double p) {
    int rand_value;
    rand_value = rand_r(rng);
    double n = rand_value / (double)RAND_MAX;
    return n < p;
}

void *inhabitant_thread_fn(void *args) {
     inhabitant_params_t params = *(inhabitant_params_t *)args;

    printf("start of inhabitant #%d\n", params.id);

    while(true) {

    }
    return NULL;
}
