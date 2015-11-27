/*********
** bank.c
** The bank
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bank.h"
#include "util.h"

/*********
** Initialize the bank
** bank : ptr to the bank structure
** nb_inhabitants : number of inhabitants
**********/
void init_bank(bank_t *bank, uint32_t nb_inhabitants) {
  int sem_return;
  bank->t = 1;
  sem_return = sem_init(&bank->mutex_t, 0, 1);
  CHECK_EXIT(sem_return != 0, "can't init mutex_t");
  bank->t_in_service = 0;
  sem_return = sem_init(&bank->mutex_t_in_service, 0, 1);
  CHECK_EXIT(sem_return != 0, "can't init mutex_t_in_service");
  sem_return = sem_init(&bank->mutex_queue, 0, 1);
  CHECK_EXIT(sem_return != 0, "can't init mutex_queue");
  sem_return = sem_init(&bank->waiting_inhabitants, 0, 0);
  CHECK_EXIT(sem_return != 0, "can't waiting_inhabitants");
  bank->queue_size = nb_inhabitants;
  bank->queue = malloc(sizeof(queue_element_t) * nb_inhabitants);
  for (uint32_t i = 0; i < nb_inhabitants; i++) {
    sem_return = sem_init(&bank->queue[i].wake_sem, 0, 0);
    CHECK_EXIT(sem_return != 0, "can't waiting_inhabitants");
    bank->queue[i].t = 0;
    bank->queue[i].is_away = false;
  }
}

/*********
** Get the next ticket
** bank : ptr to the bank structure
** returns a ticket number
**********/
uint32_t get_ticket(bank_t *bank) {
  uint32_t t;
  sem_wait(&bank->mutex_t);
  t = bank->t++;
  sem_post(&bank->mutex_t);
  return t;
}

/*********
** Check if the given ticket is expired
** bank : ptr to the bank structure
** t : given ticket number
** return true : expired / false : not expired
**********/
bool get_ticket_expired(bank_t *bank, uint32_t t) {
  bool ticket_expired;
  sem_wait(&bank->mutex_t);
  sem_wait(&bank->mutex_t_in_service);
  ticket_expired = t < bank->t_in_service;
  sem_post(&bank->mutex_t_in_service);
  sem_post(&bank->mutex_t);
  return ticket_expired;
}

/*********
** Make an inhabitant stands in line
** bank : ptr to the bank structure
** id : inhabitant's id
**********/
void stand_in_line(bank_t *bank, uint32_t id) {
  sem_post(&bank->waiting_inhabitants);
  // Inhabitant will wait till bank manager wake him
  sem_wait(&bank->queue[id].wake_sem);
}

/*********
** Get the number of inhabitants with a ticket before the given ticket number
** bank : ptr to the bank structure
** t : the given ticket number
** return the number of inhabitants with a ticket before the given ticket number
**********/
uint32_t get_inhabitant_before(bank_t *bank, uint32_t t) {
  uint32_t result;
  sem_wait(&bank->mutex_t_in_service);
  result = t - bank->t_in_service;
  sem_post(&bank->mutex_t_in_service);
  return result;
}
