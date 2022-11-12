#ifndef SERV_CLIENT_FIFO_H_
#define SERV_CLIENT_FIFO_H_

const int NMAX = 3;

char Named_pipe1[50]="./fifo1";
char Named_pipe2[50]="./fifo2";

typedef struct {	    
	char question[100];
	int pid_client;
	int nbre_aleatoire;
}Client_Question;

typedef struct {	    
	int reponse[100];
	int pid_serveur;
}Server_Response;

#endif
