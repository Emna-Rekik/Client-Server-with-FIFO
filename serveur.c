#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "headers/serv_cli_fifo.h"
#include "headers/Handlers_Serv.h"


int main(int argc, char* argv[]) {

    /*Déclarations */
    Client_Question cli_question;
    Server_Response serv_response;

    struct sigaction sa;
    sa.sa_flags = 0;

    /* Création des tubes nommés */
    int f1 = mkfifo(Named_pipe1, 0666);
    int f2 = mkfifo(Named_pipe2, 0666);

    if (f1 < 0 || f2 < 0) {
        perror("mkfifo");
        exit(1);
    }

    /* Installation des Handlers */
    //signal(SIGUSR1, hand_reveil);
    sa.sa_handler = &hand_reveil;
    sigaction(SIGUSR1, &sa, NULL);

    for (int i = 0; i < NSIG; i++) {
        if (i != 10 && i != 16 && i != 30) {
          //signal(i, fin_serveur);
          sa.sa_handler = &fin_serveur;
          sigaction(i, &sa, NULL);
        }
    }

    while(1)
    {
    	/* Ouverture des tubes nommés */
    	int fd_read = open("fifo1", O_RDONLY);
        if (fd_read == -1) {
           perror("open");
           return 1;
        }

        /* lecture d’une question */
        if (read(fd_read, &cli_question, sizeof(Client_Question)) == -1) {
            perror("write");
            return 2;
        }

        printf("Le PID de client est %d\n", cli_question.pid_client);
        printf("%s\n", cli_question.question);

        close(fd_read);

        serv_response.pid_serveur = getpid();

        /* construction de la réponse */
        int rep;
        for(int i=0; i < cli_question.nbre_aleatoire; i++)
        {
            rep = rand()%1000;
            serv_response.reponse[i] = rep;
        }

        /* Ouverture des tubes nommés */
        int fd_write = open("fifo2", O_WRONLY);
        if (fd_write == -1) {
    	    perror("open");
    	    return 1;
        }

        /* envoi de la réponse */
        if (write(fd_write, &serv_response, sizeof(Server_Response)) == -1) {
            perror("write");
            return 2;
        }

        for(int i=0; i < cli_question.nbre_aleatoire; i++){

            printf("Send %d\n", serv_response.reponse[i]);
        }

        /* envoi du signal SIGUSR1 au client conserné*/
        kill(cli_question.pid_client, SIGUSR1);
        //kill(cli_question.pid_client, SIGUSR1);

        close(fd_write);
        pause();
    }
    return 0;
}
