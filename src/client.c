/**
 * @file client.c
 * @authors Mahamat Ouagal & Tursunov Serzhan 
 * @brief fonctionnement et le main du client au cours du programme
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/fonctions.h"

int main (int argc, char **argv)
{
    tune_terminal ();
    init_graphics ();

    if (argc != 4)
    {
        printf ("Usage : %s adress_ip_serveur numéro_de_port" 
                             "nombre_de_joueur\n ", argv[0]);
        exit (-1);
    }
    
    int sockfd;               
    SAI  my_addr;    
    socklen_t addrlen = sizeof (my_addr);    

    // creation de la socket client
    sockfd = sock_client (atoi (argv[2]), argv[1], &my_addr);

    // connection au serveur
    CHECK ( (connect( sockfd, (struct sockaddr *)&my_addr, addrlen)));
    struct client_init_infos nbrJoueur;

    nbrJoueur.nb_players = atoi (argv[3]);
    
    // envoi du nombre de joueur derriere le client
    CHECK (send (sockfd, &nbrJoueur, sizeof (struct client_init_infos), 0));

    fd_set lecture, tmp;

    FD_ZERO (&lecture);
            
    FD_SET (STDIN, &lecture);
    FD_SET (sockfd, &lecture);

    tmp = lecture;
    struct timeval timer;
    timer.tv_sec = 0.5;
    

    infoRefresh numIdRefresh;
    // reception de son id et du refresh rate
    CHECK (recv (sockfd, &numIdRefresh, sizeof (infoRefresh), 0));

    int refresh_rate=numIdRefresh.refresh_rate;

    struct client_input deplacementJoueur;
    deplacementJoueur.id = numIdRefresh.id;

    // preparation et reception du plateau de jeu    
    display_info plateau_du_jeu;

    CHECK (recv (sockfd, &plateau_du_jeu, sizeof (display_info), 0));

    // affichage du plateau au debut du jeu
    clear ();
    my_draw_window (plateau_du_jeu.board);
    refresh ();

    int play = TRUE;
      
    

    while (play)
    {
    	CHECK (select (sockfd + 1, &tmp, NULL, NULL, &timer));

    	if (FD_ISSET (STDIN, &tmp))
        {
            read (STDIN, &deplacementJoueur.input, sizeof (char));

            CHECK (send (sockfd, &deplacementJoueur,
                  sizeof (struct client_input), 0));

    	}

    	if (FD_ISSET (sockfd, &tmp))
        {
    	    CHECK (recv (sockfd, &plateau_du_jeu, sizeof (display_info), 0));

            if (winner (plateau_du_jeu))
            {
                clear ();
                draw_winner (plateau_du_jeu.board, plateau_du_jeu.winner);
                refresh ();
            }
            else if (plateau_du_jeu.winner == QUIT)
            {   
                play = FALSE;

                // fermeture de la socket
                CHECK (close (sockfd));
                printf(" fin du game\n");


            }
            else
            {
                clear ();
                my_draw_window (plateau_du_jeu.board);
                refresh ();
            }
   
    	}
    	tmp = lecture;
        timer.tv_sec = 0.5;

        usleep (refresh_rate); 
    }   
    
    return 0;

}
