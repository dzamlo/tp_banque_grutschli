#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "bank_manager.h"


/*********
** The bank manager's thread
** args : ptr to the bank_manager_params_t structure
**********/
void *bank_manager_thread_fn(void *args) {
  bank_manager_params_t params = *(bank_manager_params_t *)args;

  printf("bank manager: start\n");

  while (true) {
    //Get next ticket to process
    sem_wait(&params.bank->mutex_t_in_service);
    params.bank->t_in_service++;
    sem_post(&params.bank->mutex_t_in_service);
//Only for debug
#ifndef NDEBUG
    int sval;
    sem_getvalue(&params.bank->waiting_inhabitants, &sval);
    printf("bank manager: %d inhabitant(s) waiting\n", sval);
#endif
//*****
    //Process the next inhabitant in the queue
    sem_wait(&params.bank->waiting_inhabitants);
    printf("bank manager: there is at leat one  waiting inhabitant\n");
    //Lock queue
    sem_wait(&(params.bank->mutex_queue));
    //Find the inhabitant in the queue with the right ticket number
    for (uint32_t i = 0; i < params.bank->queue_size; i++) {
      if (params.bank->queue[i].t == params.bank->t_in_service) {
        //Check if inhabitant is away while it's his turn
        if (!params.bank->queue[i].goes_away) {
        //Is here
          printf("bank manager start serving inhabitant #%d (ticket #%d)\n",
              i,
              params.bank->queue[i].t);
          usleep(params.d1);
          printf("bank manager has served inhabitant #%d (ticket #%d)\n",
              i,
              params.bank->queue[i].t);
          //Wake the inhabitant
          sem_post(&(params.bank->queue[i].wake_sem));
        } else {
        //Is away
          printf(
              "bank manager has not served inhabitant #%d (ticket #%d) because "
              "he is outside\n",
              i,
              params.bank->queue[i].t);
          // inhabitant who goes outiside don't post waiting_inhabitants (they are not wainting in the line)
          sem_post(&params.bank->waiting_inhabitants);
        }
        break;
      }
    }
    //Unlock queue
    sem_post(&(params.bank->mutex_queue));
  }
  return NULL;
}
