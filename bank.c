#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank.h"

void *bank_thread_fn(void *args) {
     bank_params_t params = *(bank_params_t *)args;

    printf("start of bank\n");

    while(true) {

    }
    return NULL;
}

void init_bank(bank_t *bank) {

}
