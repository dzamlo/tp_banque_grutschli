/*********
** bank_manager.h
** The bank manager : header file
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "bank.h"

typedef struct bank_manager_params_st {
  bank_t *bank;
  unsigned int d1;
} bank_manager_params_t;

void *bank_manager_thread_fn(void *args);

#endif
