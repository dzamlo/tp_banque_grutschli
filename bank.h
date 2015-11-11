#ifndef BANK_H
#define BANK_H

#include <stdint.h>

#include <semaphore.h>

typedef struct bank_st {
     uint32_t t;
     sem_t mutex_t;
     uint32_t t_in_service;
     sem_t mutex_t_in_service;
} bank_t;


void init_bank(bank_t *bank);
uint32_t get_ticket(bank_t *bank);

#endif
