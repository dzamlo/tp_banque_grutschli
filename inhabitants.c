#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

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
         sleep(params.d0);
         uint32_t t = get_ticket(params.bank);
         printf("inhabitans #%d got ticket %d\n", params.id, t);
    }
    return NULL;
}
