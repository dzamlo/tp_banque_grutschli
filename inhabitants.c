#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "inhabitants.h"

void *inhabitant_thread_fn(void *args) {
     inhabitant_params_t params = *(inhabitant_params_t *)args;

    printf("start of inhabitant #%d\n", params.id);

    while(true) {

    }
    return NULL;
}
