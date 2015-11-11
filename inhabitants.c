#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "inhabitants.h"


bool goes_away(unsigned int *rng, double p) {
    int rand_value;
    rand_value = rand_r(rng);
    double n = rand_value / (double)RAND_MAX;
    return n < p;
}

void *inhabitant_thread_fn(void *args) {
     inhabitant_params_t params = *(inhabitant_params_t *)args;

    printf("start of inhabitant #%d\n", params.id);

    while(true) {
         sleep(params.d0);
         uint32_t t = get_ticket(params.bank);
		
         //what if the bank_manager check  the 	queue between get_tciket and stand_in_line()
         printf("inhabitans #%d got ticket %d\n", params.id, t);
         &params.bank.queue[params.id].t = t;

         uint32_t inhabitant_before = get_inhabitant_before(bank, t);

         if(inhabitant_before > 3 && goes_away(&params.rng, params.p) {
              sleep(inhabitant_before*params.d1);
              //if ticket not used -> stand_in line
              // else sem_post waiting_inhabitants
         } else {
             // the inhabitants decided to wait in the queue
             stand_in_line(&params.bank, params.id);
         }
         
    }
    return NULL;
}
