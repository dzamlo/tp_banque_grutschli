/*********
** inhabitant.c
** An inhabitant
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "inhabitants.h"

/*********
** Compute a random value to decide if the inhabitant goes away or start stand in line
** rng : the seed for random
** p : probability of go away
** return a boolean (goes way or not)
**********/
bool decide_goes_away(unsigned int *rng, double p) {
  int rand_value;
  rand_value = rand_r(rng);
  double n = rand_value / (double)RAND_MAX;
  return n < p;
}

/*********
** The inhabitant thread function 
** args : structure with inhabitant's arguments
**********/
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
	  //Lock critical section (protect tickets incrementation)
      sem_wait(&(params.bank->mutex_queue));
      uint32_t t = get_ticket(params.bank);
      params.bank->queue[id].t = t;
      printf("inhabitant #%d got ticket %d\n", id, t);
      uint32_t inhabitant_before = get_inhabitant_before(params.bank, t);
	  //Decide to goes way or not
      bool is_away =
          inhabitant_before > 3 && decide_goes_away(&params.rng, params.p);
      params.bank->queue[id].is_away = is_away;
	  //End of critical section
      sem_post(&(params.bank->mutex_queue));
      //Inhabitant decided to goes away
      if (is_away) {
        printf("inhabitant #%d goes away\n", id);
		//Waiting (is outside)
        usleep(inhabitant_before * params.d1);
        printf("inhabitant #%d returned to the bank\n", id);
		//Lock critical section
        sem_wait(&(params.bank->mutex_queue));
		//Get if his ticket is already passed
        ticket_expired = get_ticket_expired(params.bank, t);
        if (ticket_expired) {
          printf("inhabitant #%d ticket expired\n", id);
        }
        params.bank->queue[id].is_away = false;
		//End of ctitical section
        sem_post(&(params.bank->mutex_queue));

      } else {
        printf("inhabitant #%d doesn't goes away\n", id);
      }

	  //Inhabitant is in the bank and his ticket is valid 
      if (!is_away || !ticket_expired) {
        printf("inhabitant #%d stands in line\n", id);
		//Inhabitant wait in the queue : asleep
        stand_in_line(params.bank, id);
        take_ticket = false;
        printf("inhabitant #%d has been served\n", id);
      }
    }
  }
  return NULL;
}
