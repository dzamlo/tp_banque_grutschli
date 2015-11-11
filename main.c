#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void usage(char *argv0) {
    printf("Usage:\n");
    printf("%s <nb_inhabitants> <d1> <p>\n", argv0);
}

int main(int argc, char *argv[]) {
    unsigned int d1;
    uint32_t nb_inhabitants;
    double p;
    if(argc != 4) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    d1 = atoi(argv[1]);
    nb_inhabitants = atoi(argv[2]);
    p = atof(argv[3]);
    printf("%d %d %f\n", d1, nb_inhabitants, p);
    

    return EXIT_SUCCESS;
}
