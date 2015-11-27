/*********
** bank_manager.c
** The bank manager : manage the bank and the inhabitants
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "bank_manager.h"

/*********
** The bank manager thread frunction
** args : structure with bank manager's arguments
**********/
void *bank_manager_thread_fn(void *args) {
  bank_manager_params_t params = *(bank_manager_params_t *)args;

  printf("bank manager: start\n");

  while (true) {
    // Lock access to t_in_service
    sem_wait(&params.bank->mutex_t_in_service);
    params.bank->t_in_service++;
    // Unlock access to t_in_service
    sem_post(&params.bank->mutex_t_in_service);
#ifndef NDEBUG
    int sval;
    sem_getvalue(&params.bank->waiting_inhabitants, &sval);
    printf("bank manager: %d inhabitant(s) waiting\n", sval);
#endif
    // Fall asleep if there isn't any inhabitant in the queue
    sem_wait(&params.bank->waiting_inhabitants);
    printf("bank manager: there is at least one  waiting inhabitant\n");
    // Lock access to the queue
    sem_wait(&(params.bank->mutex_queue));
    // Check all inhabitants to find the one with the right ticket
    for (uint32_t i = 0; i < params.bank->queue_size; i++) {
      if (params.bank->queue[i].t == params.bank->t_in_service) {
        if (!params.bank->queue[i].is_away) {
          // Inhabitant is here
          printf("bank manager start serving inhabitant #%d (ticket #%d)\n",
              i,
              params.bank->queue[i].t);
          usleep(params.d1);
          printf("bank manager has served inhabitant #%d (ticket #%d)\n",
              i,
              params.bank->queue[i].t);
          // Wake inhabitant
          sem_post(&(params.bank->queue[i].wake_sem));
        } else {
          // Inhabitant is away
          printf(
              "bank manager has not served inhabitant #%d (ticket #%d) because "
              "he is outside\n",
              i,
              params.bank->queue[i].t);
          // inhabitant who goes outside don't post waiting_inhabitants (they
          // are not waiting in the line)
          sem_post(&params.bank->waiting_inhabitants);
        }
        break;
      }
    }
    // Unlock access to the queue
    sem_post(&(params.bank->mutex_queue));
  }
  return NULL;
}
