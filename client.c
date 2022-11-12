#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#include "headers/serv_cli_fifo.h"
#include "headers/Handlers_Cli.h"


int main(int argc, char* argv[]) {

	/* Déclarations */
	Client_Question cli_question;
	Server_Response serv_response;

    	struct sigaction sa;
	sa.sa_flags = 0;

	/* Installation des Handlers */
	//signal(SIGUSR1,hand_reveil);
	sa.sa_handler = &hand_reveil;
        sigaction(SIGUSR1, &sa, NULL);

	/* Ouverture des tubes nommés */
	int fd_write = open("fifo1", O_WRONLY);
	if (fd_write == -1) {
	    perror("open");
	    return 1;
	}

	/* Construction et envoi d’une question */
	srand(time(NULL));
	cli_question.nbre_aleatoire = rand() % 10 + 1;
	strcpy(cli_question.question, "Envoie moi ");
	char nbre_ale[10];
	sprintf(nbre_ale, "%i", cli_question.nbre_aleatoire);
	strcat(cli_question.question, nbre_ale);
	strcat(cli_question.question, " nombres aléatoire");

	cli_question.pid_client = getpid();
	int question_size = strlen(cli_question.question);

	if (write(fd_write, &cli_question, sizeof(Client_Question)) == -1) {
	    perror("write");
	    return 2;
	}

	close(fd_write);

	/* Ouverture des tubes nommés */
	int fd_read = open("fifo2", O_RDONLY);
	if (fd_read == -1) {
	    perror("open");
	    return 1;
	}

	/* Attente de la réponse */
	pause();

	/* Lecture de la réponse */
	if (read(fd_read, &serv_response, sizeof(Server_Response)) == -1) {
		perror("read");
		return 2;
	}

	/* Envoi du signal SIGUSR1 au serveur */
	kill(serv_response.pid_serveur, SIGUSR1);

	/* Traitement local de la réponse */
	for(int i=0; i < cli_question.nbre_aleatoire; i++)
	{
	    printf("Received %d\n", serv_response.reponse[i]);
	}
	printf("Le PID serveur est %d\n", serv_response.pid_serveur);

	close(fd_read);

    return 0;
}
