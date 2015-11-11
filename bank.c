#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank.h"
#include "util.h"

void init_bank(bank_t *bank, uint32_t nb_inhabitants) {
    int sem_return;
    bank->t = 1;
    sem_return = sem_init(&bank->mutex_t, 0, 1);
    CHECK_EXIT(sem_return != 0, "can't init mutex_t");
    bank->t_in_service = 0;
    sem_return = sem_init(&bank->mutex_t_in_service, 0, 1);
    CHECK_EXIT(sem_return != 0, "can't init mutex_t_in_service");
    sem_return = sem_init(&bank->waiting_inhabitants, 0, 0);
    CHECK_EXIT(sem_return != 0, "can't waiting_inhabitants");
    bank->queue = malloc(sizeof(queue_element_t) * nb_inhabitants);
    for(uint32_t i = 0; i < nb_inhabitants; i++) {
        sem_return = sem_init(&bank->queue[i].wake_sem, 0, 0);
        CHECK_EXIT(sem_return != 0, "can't waiting_inhabitants");
        bank->queue[i].t = 0;
        bank->queue[i].waiting = false;
    }

}

uint32_t get_ticket(bank_t *bank) {
    uint32_t t;
    sem_wait(&bank->mutex_t);
    t = bank->t++;
    sem_post(&bank->mutex_t);
    return t;
}

void stand_in_line(bank_t *bank, uint32_t id) {
     bank_queue[i].waiting = true;
     sem_post(&bank->waiting_inhabitants);
     sem_wait(&bank.queue[i].wake_sem);
}

uint32_t inhabitant_before(bank_t *bank, uint32_t t) {
    uint32_t result;
    sem_wait(&bank->mutex_t_in_service);
    result = t - bank->t_in_service;
    sem_post(&bank->mutex_t_in_service);
    return result;
}
