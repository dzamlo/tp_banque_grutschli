#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank_manager.h"

void *bank_manager_thread_fn(void *args) {
     bank_manager_params_t params = *(bank_manager_params_t *)args;

    printf("start of bank\n");

    while(true) {
        sem_wait(&bank->mutex_t_in_service);
        bank->t_in_service++;
        sem_post(&bank->mutex_t_in_service);

        sem_wait(&params.bank->waiting_inhabitants);
        
        printf("bank manager: there is at leat one  waiting inhabitant\n");
    }
    return NULL;
}
