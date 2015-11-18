#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "inhabitants.h"

bool decide_goes_away(unsigned int *rng, double p) {
  int rand_value;
  rand_value = rand_r(rng);
  double n = rand_value / (double)RAND_MAX;
  return n < p;
}

void *inhabitant_thread_fn(void *args) {
  bool take_ticket;
  bool ticket_expired;
  inhabitant_params_t params = *(inhabitant_params_t *)args;
  uint32_t id = params.id;

  printf("inhabitant #%d: start\n", params.id);

  while (true) {
    usleep(params.d0);
    take_ticket = true;
    while (take_ticket) {
      sem_wait(&(params.bank->mutex_queue));
      uint32_t t = get_ticket(params.bank);
      params.bank->queue[id].t = t;
      printf("inhabitant #%d got ticket %d\n", id, t);
      uint32_t inhabitant_before = get_inhabitant_before(params.bank, t);
      bool goes_away =
          inhabitant_before > 3 && decide_goes_away(&params.rng, params.p);
      params.bank->queue[id].goes_away = goes_away;
      sem_post(&(params.bank->mutex_queue));

      if (goes_away) {
        printf("inhabitant #%d goes away\n", id);
        usleep(inhabitant_before * params.d1);
        printf("inhabitant #%d returned to the bank\n", id);
        sem_wait(&(params.bank->mutex_queue));
        ticket_expired = get_ticket_expired(params.bank, t);
        if (ticket_expired) {
          printf("inhabitant #%d ticket expired\n", id);
        }
        params.bank->queue[id].goes_away = false;
        sem_post(&(params.bank->mutex_queue));

      } else {
        printf("inhabitant #%d doesn't goes away\n", id);
      }

      if (!goes_away || !ticket_expired) {
        printf("inhabitant #%d stands in line\n", id);
        stand_in_line(params.bank, id);
        take_ticket = false;
        printf("inhabitant #%d has been served\n", id);
      }
    }
  }
  return NULL;
}
