#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void hand_reveil(int sig) {
    printf("Le client a lu les reponses\n\n");
}

void fin_serveur(int sig){
    char Named_pipe1[50]="./fifo1";
    char Named_pipe2[50]="./fifo2";
    unlink(Named_pipe1);
    unlink(Named_pipe2);
    printf("exit serveur\n");
    exit(0);
}

