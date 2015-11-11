#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank_manager.h"

void *bank_manager_thread_fn(void *args) {
     bank_manager_params_t params = *(bank_manager_params_t *)args;

    printf("start of bank\n");

    while(true) {

    }
    return NULL;
}
