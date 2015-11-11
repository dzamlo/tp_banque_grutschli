#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "inhabitants.h"

void usage(char *argv0) {
    printf("Usage:\n");
    printf("%s <nb_inhabitants> <d1> <p>\n", argv0);
}

int main(int argc, char *argv[]) {
    unsigned int d1, d0;
    uint32_t nb_inhabitants;
    double p;
    if(argc != 4) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    nb_inhabitants = atoi(argv[1]);
    d1 = atoi(argv[2]);
    p = atof(argv[3]);
    d0 = 10*d1;
    
    
    inhabitant_params_t inhabitants_params[nb_inhabitants];
    pthread_t inhabitants_threads[nb_inhabitants];
    for(uint32_t i = 0; i < nb_inhabitants; i++) {
        inhabitants_params[i].id = i;
        inhabitants_params[i].d0 = d0;
        inhabitants_params[i].d1 = d1;
        inhabitants_params[i].p = p;

        pthread_create(&inhabitants_threads[i], NULL, inhabitant_thread_fn, &inhabitants_params[i]);
        
    }
    
    pthread_exit(NULL);
    //return EXIT_SUCCESS;
}
