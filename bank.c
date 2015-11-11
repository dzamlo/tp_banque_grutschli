#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank.h"
#include "util.h"

void init_bank(bank_t *bank) {
    int sem_return;
    bank->t = 0;
    sem_return = sem_init(&bank->mutex_t, 0, 1);
    CHECK_EXIT(sem_return != 0, "can't init mutex_t");
    bank->t_in_service = 0;
    sem_return = sem_init(&bank->mutex_t_in_service, 0, 1);
    CHECK_EXIT(sem_return != 0, "can't init mutex_t_in_service");

}

uint32_t get_ticket(bank_t *bank) {
    uint32_t t;
    sem_wait(&bank->mutex_t);
    t = bank->t++;
    sem_post(&bank->mutex_t);
    return t;
}
