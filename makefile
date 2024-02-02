CC=gcc
CFLAGS1 = -g -c -Wall -Wextra -Werror 
LDFLAGS= -lncurses

vpath %.h include
vpath %.c src
vpath %.o obj

OBJ=obj/
SRC=src/


serveur : serveur.o fonction.o
	$(CC) -g -o serveur $(OBJ)serveur.o $(OBJ)fonction.o $(LDFLAGS)
	@mkdir -p bin
	mv -f serveur ./bin

serveur.o : serveur.c  fonctions.h
	$(CC) $(CFLAGS1) $(SRC)serveur.c 
	@mkdir -p obj
	mv -f serveur.o ./obj


fonction.o: fonction.c fonctions.h
	$(CC) $(CFLAGS1) $(SRC)fonction.c  
	mv -f fonction.o ./obj


client: client.o fonction.o
	$(CC) -g -o  client $(OBJ)client.o $(OBJ)fonction.o $(LDFLAGS)
	mv -f client ./bin

client.o : client.c  fonctions.h
	$(CC)  $(CFLAGS1) $(SRC)client.c 
	mv -f client.o ./obj




clean :	
	rm -rf bin/serveur bin/client
	rm -rf obj/
	rm -rf doc/
	rm -rf bin/

docs:
	@mkdir -p doc
	doxygen Doxyfile
	mv html latex ./doc


dist: makefile src include bin obj Doxyfile rapport-MAHAMAT-TURSUNOV.pdf
	tar -cvz $^ -f projet-version-x.tar.xz







