/**
 * @file fonction.c
 * @authors Mahamat Ouagal & Tursunov Serzhan 
 * @brief implementation des fonctions nécessaire pour le déroulement du jeu   
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/fonctions.h"



void tune_terminal ()
{
    struct termios term;
    tcgetattr (0, &term);
    term.c_iflag &= ~ICANON;
    term.c_lflag &= ~ICANON;
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 0;
    tcsetattr (0, TCSANOW, &term);
}

void init_graphics ()
{
    initscr ();
    cbreak ();
    noecho ();
    keypad (stdscr, TRUE);
    curs_set (0);
    timeout (100);
    start_color ();
    init_pair (BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair (RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair (YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair (MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair (CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);

    init_pair (BLUE_ON_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair (RED_ON_RED, COLOR_RED, COLOR_RED);
    init_pair (YELLOW_ON_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair (MAGENTA_ON_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair (CYAN_ON_CYAN, COLOR_CYAN, COLOR_CYAN);

    init_pair (WALL, COLOR_WHITE, COLOR_WHITE);
}


void display_character (int color, int y, int x, char character) 
{
    attron (COLOR_PAIR (color));
    mvaddch (y, x, character);
    attroff (COLOR_PAIR (color));
}

void my_window_init (char board [XMAX][YMAX])
{
    for (size_t i = 0; i < XMAX; i++)
    {
        for (size_t j = 0; j < YMAX; j++)
        {
            if (i == 0 || i == XMAX - 1) 
            {
                board[i][j] = WALL;
            } 
            else if (j == 0 || j == YMAX - 1) 
            {

                board[i][j] = WALL;
            }
            else 
            {
                 board[i][j] = '*';
            } 
        }
    }
 
}


void my_draw_window (char board[XMAX][YMAX])
{
   for (size_t i = 0; i < XMAX; i++)
   {
        for (size_t j = 0; j < YMAX; j++)
        {
            if (i == 0 || i == XMAX - 1)
            {
                display_character (CYAN_ON_CYAN, i, j, ACS_VLINE);
            }
            else if (j == 0 || j == YMAX - 1) 
            {
                display_character (CYAN_ON_CYAN, i, j, ACS_HLINE);
            } 
            else 
            {
                if (board[i][j] == 50)
                { 
                    display_character (RED_ON_BLACK + TRAIL_INDEX_SHIFT,
                                                            i, j, 'X');
                }
                if (board[i][j] == 0)
                {
                    display_character (RED_ON_BLACK, i, j, 'X');
                }
                if (board[i][j] == 1) 
                {
                    display_character (BLUE_ON_BLACK, i, j, 'Z');
                }
                else if (board[i][j] == 51)
                {
                    display_character (BLUE_ON_BLACK + TRAIL_INDEX_SHIFT,
                                                              i, j, 'Z');            
                }
            }
        }

        mvaddstr (0, YMAX / 2 - strlen ("C-TRON") / 2, "C-TRON");
    }
}


int my_random (int min, int max)
{
    int x = min + rand () % (max + 1 - min);
    return x;
}


void initPosition (players_position * positions)
{    
    positions->x1 = my_random (1, XMAX / 2);
    positions->x2 = my_random (1, XMAX / 2);
    positions->y1 = my_random (1, YMAX / 2);
    positions->y2 = my_random (1, YMAX / 2);
}


int movement_multi_client (char input, players_position * positionDesJoueurs,
                            display_info * plateau_du_jeu, int id, int light)
{

    int valeur_de_retour = FALSE;
    

    switch (input)
    {
        case 'z':

            if (id == 0)
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->x1 -= 1;
                if ( (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                           positionDesJoueurs->y1, id))) 
                {
                    valeur_de_retour = TRUE;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 0;
                    return FALSE;
                }
            }

            else
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->x2 -= 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                          positionDesJoueurs->y2, id))
                {     
                    valeur_de_retour = TRUE;
                }
                
                else
                {

                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;

                    return FALSE;
                }

            }

            break;


        case 'q':
        
            if (id == 0)
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                          [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->y1 -= 1;

                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                   positionDesJoueurs->y1, id))
                {
                   valeur_de_retour = TRUE;
                }

                else plateau_du_jeu->board[positionDesJoueurs->x1]
                                          [positionDesJoueurs->y1] = 0;
            }
            else
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->y2 -= 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                          positionDesJoueurs->y2, id))
                {                          
                    valeur_de_retour = TRUE;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }
            }

            break;

        case 'd':

            if (id == 0)
            {    
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->y1 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                          positionDesJoueurs->y1, id)) 
                {
                    valeur_de_retour = TRUE;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 0;
                }
            }
            else
            {
                if (light) 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->y2 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                          positionDesJoueurs->y2, id))
                {                          
                    valeur_de_retour = TRUE;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }            
            }

            break;

        case 's':

            if (id == 0)
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->x1 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                          positionDesJoueurs->y1, id))
                {
                    valeur_de_retour = TRUE;
                }
                else plateau_du_jeu->board[positionDesJoueurs->x1]
                                          [positionDesJoueurs->y1] = 0;
            }
            else
            {
                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->x2 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                          positionDesJoueurs->y2, id))
                {
                    valeur_de_retour = TRUE;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }            
            }
        
        default:
        
            break;
    }

    return valeur_de_retour;
}

int collision (display_info * plateau_du_jeu, int x, int y, int id)
{
    if (plateau_du_jeu->board[x][y] == 50 || plateau_du_jeu->board[x][y] == 51
                                       || plateau_du_jeu->board[x][y] == WALL)
    {
        plateau_du_jeu->winner = (id + 1) % 2;

        return TRUE;
    }
 
    if ( ( (id == 0) && (plateau_du_jeu->board[x][y] == 1)) || ( (id == 1) &&
                                        (plateau_du_jeu->board[x][y] == 0 )))
    {
        plateau_du_jeu->winner = TIE;
        
        return TRUE;
    }

    return FALSE;    
}


int winner (display_info plateau_dujeu)
{
    if (plateau_dujeu.winner == -1) return FALSE;

    return TRUE;
}


void draw_winner (char board[XMAX][YMAX], int winnerid)
{
    for (size_t i = 0; i < XMAX; i++)
    {
        for (size_t j = 0; j < YMAX; j++)
        {
            if (board [i][j] == WALL)
            {
                display_character (CYAN_ON_CYAN, i, j, ACS_VLINE);
            }
           
        }

    }
    mvaddstr (0, YMAX / 2 - strlen ("C-TRON") / 2, "C-TRON");

    if (winnerid == 0)
    {  
        mvaddstr (XMAX / 2, YMAX / 2 - strlen ("gagnant joueur X (rouge)"),
                                               "gagnant joueur X (rouge)");
    }
    if (winnerid == TIE)
    {
        mvaddstr (XMAX / 2, YMAX / 2 - strlen ("egalité parfaite"),
                                               "égalité parfaite");
    }
    if (winnerid == 1)
    {
        mvaddstr (XMAX / 2, YMAX / 2 - strlen("gagnant joueur Z (bleue)"),
                                              "gagnant joueur Z (bleue)");
    }
}


int sock_server (int port, char * adrIP, SAI * my_addr)
{
    int sockfd;
    
    CHECK (sockfd = socket (AF_INET, SOCK_STREAM, 0));
    
    my_addr->sin_family = AF_INET;
    my_addr->sin_port = htons (port);
    inet_aton (adrIP, &(my_addr->sin_addr));

    CHECK (bind (sockfd, (struct sockaddr *) my_addr,
                       sizeof (struct sockaddr_in)));

    return sockfd;
}


int sock_client (int port, char * adrIP, SAI * my_addr)
{
    int sockfd;
    
    CHECK (sockfd = socket (AF_INET, SOCK_STREAM, 0));
    
    my_addr->sin_family = AF_INET;
    my_addr->sin_port = htons (port);
    inet_aton (adrIP, &(my_addr->sin_addr));

    return sockfd;
}


int movement_single_client (char input, players_position * positionDesJoueurs,
                                     display_info * plateau_du_jeu, int light)
{
    int valeur_de_retour = FALSE;
    
    switch (input)
    {
        case 'z':

            if (light)
            {
                plateau_du_jeu->board[positionDesJoueurs->x1]
                                     [positionDesJoueurs->y1] = 50;
            }
            else  
            {
                plateau_du_jeu->board[positionDesJoueurs->x1]
                                     [positionDesJoueurs->y1] = '*';
            }

            positionDesJoueurs->x1 -= 1;
            
            if ( (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                        positionDesJoueurs->y1, 0)))
            {
                valeur_de_retour = TRUE;
            }
            else
            {
                plateau_du_jeu->board[positionDesJoueurs->x1]
                                     [positionDesJoueurs->y1] = 0;  
            }

            break;

        case 'q':

                if (light) 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->y1 -= 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                           positionDesJoueurs->y1, 0)) 
                {
                    valeur_de_retour = TRUE ;
                }
                else plateau_du_jeu->board[positionDesJoueurs->x1]
                                          [positionDesJoueurs->y1] = 0;
                                  
            break;

        case 'd':

                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->y1 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                          positionDesJoueurs->y1, 0))
                {
                    valeur_de_retour = TRUE;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 0;
                }                
            break;

        case 's':

                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 50;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = '*';
                }

                positionDesJoueurs->x1 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x1,
                                           positionDesJoueurs->y1, 0)) 
                {
                    valeur_de_retour = TRUE;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x1]
                                         [positionDesJoueurs->y1] = 0;
                }

            break;
        
    /*-------------------------cases du second joueur ----------------------*/

        case 'i':
            
            if (light)
            {
                plateau_du_jeu->board[positionDesJoueurs->x2]
                                     [positionDesJoueurs->y2] = 51;
            }
            else
            {
                plateau_du_jeu->board[positionDesJoueurs->x2]
                                     [positionDesJoueurs->y2] = '*';
            }

            positionDesJoueurs->x2 -= 1;
            
            if ( (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                        positionDesJoueurs->y2, 1)))
            {                            
                valeur_de_retour = TRUE;
            }
            else
            {
                plateau_du_jeu->board[positionDesJoueurs->x2]
                                     [positionDesJoueurs->y2] = 1;
            } 

            break;

        case 'j':

                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->y2 -= 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                           positionDesJoueurs->y2, 1)) 
                {    
                    valeur_de_retour = TRUE;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }   
                             
            break;

        case 'l':

                if (light)
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->y2 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                           positionDesJoueurs->y2, 1))
                {
                    valeur_de_retour = TRUE;
                }
                else 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }

            break;

        case 'k':

                if (light) 
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 51;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = '*';
                }

                positionDesJoueurs->x2 += 1;
                
                if (collision (plateau_du_jeu, positionDesJoueurs->x2,
                                           positionDesJoueurs->y2, 1))
                {
                    valeur_de_retour = TRUE;
                }
                else
                {
                    plateau_du_jeu->board[positionDesJoueurs->x2]
                                         [positionDesJoueurs->y2] = 1;
                }

            break;
            
        default:

            break;
    }
            
    return valeur_de_retour;
}


void game_single_client (int client1, struct client_input *joueur1,
                              char *lastjoueur1, char *lastjoueur2,
                              int *lightjoueur1, int *lightjoueur2,
                             players_position * positionDesJoueurs, 
                      display_info * plateau_du_jeu, int findugame,
                      fd_set *tmp, fd_set* lecture, int grandSockfd, 
            struct timeval * timer, int refresh_rate, int *begin)
{

    while (!findugame)
    { 
        CHECK (select (grandSockfd + 1, tmp, NULL, NULL, timer));              

        if (FD_ISSET (client1, tmp))
        {
    	    CHECK (recv (client1, joueur1, sizeof (struct client_input), 0));     
        }  

        if (joueur1->input == 'z' || joueur1->input == 'q' ||
                joueur1->input=='s' || joueur1->input == 'd')
        {         
            *lastjoueur1 = joueur1->input;
        }
        else if (joueur1->input == ' ')
        {
            if (*lightjoueur1) *lightjoueur1 = FALSE;
            else *lightjoueur1 = TRUE;
            
            joueur1->input = '*';
        } 
        else if (joueur1->input == 'm')
        {

            if (*lightjoueur2) *lightjoueur2 = FALSE;
            else *lightjoueur2 = TRUE;

            joueur1->input = '*';   
        }
        else if (joueur1->input == 'i' || joueur1->input == 'j'
             || joueur1->input == 'k' || joueur1->input == 'l')
        {          
            *lastjoueur2 = joueur1->input;
        }

        if (movement_single_client (*lastjoueur1, positionDesJoueurs, 
                                    plateau_du_jeu, *lightjoueur1) ||
            movement_single_client (*lastjoueur2, positionDesJoueurs,
                                      plateau_du_jeu, *lightjoueur2))
        {
            CHECK (send (client1, plateau_du_jeu, sizeof (display_info), 0));

            findugame = TRUE;
            *begin = FALSE;
        }
        else
        {
            CHECK (send (client1, plateau_du_jeu, sizeof (display_info), 0));
        }

        *tmp = *lecture;
        timer->tv_sec = 0.5;

        usleep (refresh_rate);

    }
    
}


void game_multi_client (int client1, int client2, struct client_input *joueur1,
                              struct client_input * joueur2, char *lastjoueur1,
                       char *lastjoueur2, int *lightjoueur1, int *lightjoueur2,
          players_position * positionDesJoueurs, display_info * plateau_du_jeu,
                  int findugame, fd_set *tmp, fd_set* lecture, int grandSockfd, 
                         struct timeval * timer, int refresh_rate, int * begin)
{

    while (!findugame)
    {
        CHECK (select (grandSockfd + 1, tmp, NULL, NULL, timer));

    	if (FD_ISSET (client1, tmp))
        {
    	    CHECK (recv (client1, joueur1, sizeof (struct client_input), 0));     
        } 

        if (FD_ISSET (client2, tmp))
        {                   
            CHECK (recv (client2, joueur2, sizeof (struct client_input), 0));
        }
    
        if (joueur1->input != ' ') *lastjoueur1 = joueur1->input;

        else
        {
            if (*lightjoueur1) *lightjoueur1 = FALSE;
            else *lightjoueur1 = TRUE;
            
            joueur1->input = *lastjoueur1;
        }

        if (joueur2->input !=' ') *lastjoueur2 = joueur2->input;

        else
        {
            if (*lightjoueur2) *lightjoueur2 = FALSE;
            else *lightjoueur2 = TRUE;
            
            joueur2->input = *lastjoueur2;
        }

        if (movement_multi_client (*lastjoueur1, positionDesJoueurs,
                      plateau_du_jeu, joueur1->id, *lightjoueur1) ||
            movement_multi_client (*lastjoueur2, positionDesJoueurs,
                        plateau_du_jeu, joueur2->id, *lightjoueur2))
        {
            CHECK (send (client1, plateau_du_jeu, sizeof (display_info), 0));
            CHECK (send (client2, plateau_du_jeu, sizeof (display_info), 0));

            findugame = TRUE;
            *begin = FALSE;
        }

        else
        {
            CHECK (send (client1, plateau_du_jeu, sizeof (display_info), 0));
            CHECK (send (client2, plateau_du_jeu, sizeof (display_info), 0));
        }

        *tmp = *lecture;
        timer->tv_sec = 0.5;

        usleep (refresh_rate);
    }
}


void default_init (char *lastjoueur1,char * lastjoueur2,
                           struct client_input *joueur1,
                           struct client_input *joueur2,
                   int *lightjoueur1, int *lightjoueur2,
                                        int * findugame, 
                  players_position * positionDesJoueurs,
              display_info * plateau_du_jeu, int *begin)
{
    *lastjoueur1 = '#';
    *lastjoueur2 = '#';

    joueur1->input = '#';
    joueur2->input = '#';

    *lightjoueur1 = TRUE;
    *lightjoueur2 = TRUE;

    *findugame = FALSE;
    *begin = TRUE;
    initPosition (positionDesJoueurs);
    my_window_init (plateau_du_jeu->board);
    plateau_du_jeu->winner = -1;

    plateau_du_jeu->board[positionDesJoueurs->x1][positionDesJoueurs->y1] = 0;
    plateau_du_jeu->board[positionDesJoueurs->x2][positionDesJoueurs->y2] = 1;

}







