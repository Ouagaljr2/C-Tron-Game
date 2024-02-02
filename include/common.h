#ifndef __COMMON_H__
#define __COMMON_H__


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#include <termios.h>
#include <ncurses.h>
#include <time.h>



#define STDIN 0
#define STDOUT 1

#define LENGTH 2
#define MAXUSERS 2
#define BUFFERSIZE 8
#define QUIT -3


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define TRAIL_UP 4


#define SERV_PORT 5555
#define TIE -2
#define TRAIL_INDEX_SHIFT 50

#define SA struct sockaddr
#define SAI struct sockaddr_in
#define TV struct timeval


#define XMAX 50
#define YMAX 100
#define NB_COLORS 5

#define BLUE_ON_BLACK       0
#define RED_ON_BLACK        2
#define YELLOW_ON_BLACK     1
#define MAGENTA_ON_BLACK    3
#define CYAN_ON_BLACK       4

#define BLUE_ON_BLUE        50
#define RED_ON_RED          52
#define YELLOW_ON_YELLOW    51
#define MAGENTA_ON_MAGENTA  53
#define CYAN_ON_CYAN        54

#define WALL 111

#define max(a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })



#define CHECK(op) do {				\
	if ((op) == -1) {			\
	    perror(#op);			\
	    exit(EXIT_FAILURE);			\
	}					\
    } while (0)

typedef struct display_info
{
    char board[XMAX][YMAX];
    int winner;
} display_info;

struct client_input
{
    int id;
    char input;
};

struct client_init_infos
{
    int nb_players;
};

// structure contenant les positions des joueurs en un temps t
typedef struct players_position
{
    int x1;
    int y1;
    int x2;
    int y2;
} players_position;

// structure contenant l'id et periode de reception de nouvelles frames
typedef struct infoRefresh
{
    int id;
    int refresh_rate;

}infoRefresh;



// prototypes des fonctions fournies
void tune_terminal ();
void init_graphics ();
void display_character (int color, int y, int x, char character);


#endif