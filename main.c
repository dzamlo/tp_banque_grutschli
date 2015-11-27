/*********
** main.c
** Main program
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "bank.h"
#include "bank_manager.h"
#include "inhabitants.h"
#include "util.h"

/*********
** Show usage informations
** argv0 : the program's name
**********/
void usage(char *argv0) {
  printf("Usage:\n");
  printf("%s <nb_inhabitants> <d1> <p>\n", argv0);
  printf("\n");
  printf("  nb_inhabitants: the number of inhabitants\n");
  printf("  d1: the delay d1 in microseconds\n");
  printf("  p: the probability p\n");
}

/*********
** Entry point
**********/
int main(int argc, char *argv[]) {
  int pthread_create_return;
  unsigned int d1, d0;
  uint32_t nb_inhabitants;
  double p;
  if (argc != 4) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  nb_inhabitants = atoi(argv[1]);
  d1 = atoi(argv[2]);
  p = atof(argv[3]);
  d0 = 10 * d1;

  bank_t bank;
  init_bank(&bank, nb_inhabitants);
  
  //Start bank manager
  bank_manager_params_t bank_manager_params = {&bank, d1};
  pthread_t bank_manager_thread;
  pthread_create_return = pthread_create(
      &bank_manager_thread, NULL, bank_manager_thread_fn, &bank_manager_params);
  CHECK_EXIT(pthread_create_return != 0, "can't create bank_manger thread");

  //Start inhabitants
  inhabitant_params_t inhabitants_params[nb_inhabitants];
  pthread_t inhabitants_threads[nb_inhabitants];
  for (uint32_t i = 0; i < nb_inhabitants; i++) {
    inhabitants_params[i].id = i;
    inhabitants_params[i].d0 = d0;
    inhabitants_params[i].d1 = d1;
    inhabitants_params[i].p = p;
    inhabitants_params[i].bank = &bank;
    inhabitants_params[i].rng = i;

    pthread_create_return = pthread_create(&inhabitants_threads[i],
        NULL,
        inhabitant_thread_fn,
        &inhabitants_params[i]);
    CHECK_EXIT(
        pthread_create_return != 0, "can't create one of inhabitant threads");
  }

  //Needed to prevent program from exit
  pthread_join(bank_manager_thread, NULL);
  return EXIT_SUCCESS;
}
