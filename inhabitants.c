#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "inhabitants.h"

bool goes_away(struct random_data *rng, double p) {
    int32_t rand_value;
    random_r(rng, &rand_value);
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
