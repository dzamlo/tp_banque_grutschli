#ifndef BANK_H
#define BANK_H

#include <stdbool.h>
#include <stdint.h>

#include <semaphore.h>

typedef struct queue_element_st {
  sem_t wake_sem;
  uint32_t t;
  bool is_away;
} queue_element_t;

typedef struct bank_st {
  uint32_t t;
  sem_t mutex_t;
  uint32_t t_in_service;
  sem_t mutex_t_in_service;
  sem_t waiting_inhabitants;
  sem_t mutex_queue;
  uint32_t queue_size;
  queue_element_t *queue;
} bank_t;

void init_bank(bank_t *bank, uint32_t nb_inhabitants);
uint32_t get_ticket(bank_t *bank);
bool get_ticket_expired(bank_t *bank, uint32_t t);
void stand_in_line(bank_t *bank, uint32_t id);
uint32_t get_inhabitant_before(bank_t *bank, uint32_t t);

#endif
