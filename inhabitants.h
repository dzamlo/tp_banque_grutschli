/*********
** bank_manager.c
** An inhabitant : header file
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#ifndef INHABITANTS_H
#define INHABITANTS_H

#include <stdint.h>
#include "bank.h"

typedef struct inhabitant_params_st {
  uint32_t id;
  unsigned int d1;
  unsigned int d0;
  double p;
  unsigned int rng;
  bank_t *bank;
} inhabitant_params_t;

void *inhabitant_thread_fn(void *args);

#endif
