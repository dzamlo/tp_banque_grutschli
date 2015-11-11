#ifndef BANK_H
#define BANK_H

typedef struct bank_st {

} bank_t;


typedef struct bank_params_st {
    bank_t *bank;
} bank_params_t;

void *bank_thread_fn(void *args);

void init_bank(bank_t *bank);

#endif
