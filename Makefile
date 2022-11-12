CC:= gcc
CFLAGS:= -std=c11 -O0 -Wall -g
OBJECTS_PATH:= ./objects
SOURCE_PATH:= ./sources

main : serveur client

serveur: $(OBJECTS_PATH)/Handlers_Serv.o $(OBJECTS_PATH)/serveur.o
	$(CC)  $(OBJECTS_PATH)/Handlers_Serv.o $(OBJECTS_PATH)/serveur.o -o serveur

$(OBJECTS_PATH)/Handlers_Serv.o: ./objects $(SOURCE_PATH)/Handlers_Serv.c
	@$(CC) -c $(SOURCE_PATH)/Handlers_Serv.c
	@mv Handlers_Serv.o $(OBJECTS_PATH)

$(OBJECTS_PATH)/serveur.o: ./objects ./serveur.c
	@$(CC) -c ./serveur.c
	@mv serveur.o $(OBJECTS_PATH)
	
client: $(OBJECTS_PATH)/Handlers_Cli.o $(OBJECTS_PATH)/client.o
	$(CC)  $(OBJECTS_PATH)/Handlers_Cli.o $(OBJECTS_PATH)/client.o -o client

$(OBJECTS_PATH)/Handlers_Cli.o: ./objects $(SOURCE_PATH)/Handlers_Cli.c
	@$(CC) -c $(SOURCE_PATH)/Handlers_Cli.c
	@mv Handlers_Cli.o $(OBJECTS_PATH)
	
$(OBJECTS_PATH)/client.o: ./objects ./client.c
	@$(CC) -c ./client.c
	@mv client.o $(OBJECTS_PATH)
	
	
objects:
	mkdir -p ./objects
	

