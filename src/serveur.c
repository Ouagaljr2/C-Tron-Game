/**
 * @file serveur.c
 * @authors Mahamat Ouagal & Tursunov Serzhan 
 * @brief fonctionnement et le main du serveur au cours du programme
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../include/fonctions.h"


int main (int argc, char **argv)
{
    srand (time (NULL));

    if (argc != 3)
    {
        printf ("Usage : %s numéro_de_port refresh_time \n ", argv[0]);
        exit (-1);
    }


    // variables
    int nombreJoueurs = 0;
    int client1 = 0;
    int client2 = 0;
    int clientsDifferents = FALSE;
    int refresh_rate = atoi (argv[2]);
    refresh_rate *= 1000;

    // creation de la socket du serveur
    int sockfd;                   
    SAI my_addr;
    socklen_t addrlen = sizeof (my_addr); 
    sockfd=sock_server (atoi (argv[1]), "0.0.0.0", &my_addr);
    

    CHECK ( listen (sockfd, LENGTH));

    printf ("Socket creer et Bind effectuer : le serveur vous écoutent  \n");

    CHECK (client1 = accept (sockfd, (struct sockaddr *)&my_addr, &addrlen));
    printf ("premier client connecté \n");



    struct client_init_infos donneesRecu;

    CHECK (recv (client1, &donneesRecu, sizeof (struct client_init_infos), 0));
    nombreJoueurs += donneesRecu.nb_players;

    

    if (nombreJoueurs < MAXUSERS)
    {
        clientsDifferents = TRUE;
        printf ("attente du deuxiéme client\n");
        CHECK (client2 = accept (sockfd, (struct sockaddr *)&my_addr,
                                                          &addrlen));
        printf ("deuxieme client connecté \n");
        nombreJoueurs++;
    }

    printf ("le nombre de joueurs est egale a %d maintenant le jeu peut"
                                        "commencer: \n", nombreJoueurs);

    // variables de jeu contenant les inputs et les ids des joueurs
    struct client_input joueur1;
    struct client_input joueur2;

    // sauvegarde l'ancienne direction d'un joueur
    char lastjoueur1;
    char lastjoueur2;
    
    // bool pour savoir si il faut commencer une partie
    int begin;
    // fin d'une partie
    int findugame;
    // fin du programme
    int Finduprogramme = FALSE;

    // activation ou desactivation  des lights
    int lightjoueur1;
    int lightjoueur2;

    // structure contennat la position des joueurs
    players_position positionDesJoueurs;
    display_info plateau_du_jeu;

    default_init (&lastjoueur1, &lastjoueur2, &joueur1, &joueur2,
                        &lightjoueur1, &lightjoueur2, &findugame,
                  &positionDesJoueurs, &plateau_du_jeu, &begin );


    fd_set lecture, tmp, tmp2;

    FD_ZERO (&lecture);
            
    FD_SET (client1, &lecture);
    if (clientsDifferents) FD_SET(client2, &lecture);

    tmp = lecture;
    TV timer, timer2;

    timer.tv_sec = 0.5;
    timer2.tv_sec = 0.5;

    int grandSockfd = max (client1, client2);

    char buffer[BUFFERSIZE];
     
     // ids et le refresh rate pour avoir une coordination
    infoRefresh idjoueur1;
    idjoueur1.id=0;
    idjoueur1.refresh_rate=refresh_rate;
    infoRefresh idjoueur2;
    idjoueur2.id=1;
    idjoueur2.refresh_rate=refresh_rate;

    // envoi d'ids au(x) client(s) et le refresh_rate
    CHECK (send (client1, &idjoueur1, sizeof (infoRefresh), 0));
    if (clientsDifferents) CHECK (send (client2, &idjoueur2, sizeof (infoRefresh), 0));


    // Envoi du plateau de jeu au(x) client(s)
    CHECK (send (client1, &plateau_du_jeu, sizeof (display_info), 0));
    if (clientsDifferents)
    {
        CHECK (send (client2, &plateau_du_jeu, sizeof (display_info), 0));
    }
    
    while (!Finduprogramme)
    {
        FD_ZERO (&tmp2);
        FD_SET (STDIN, &tmp2);
        
        CHECK (select (STDIN + 1, &tmp2, NULL, NULL, &timer2));

        if (FD_ISSET (STDIN, &tmp2))
        {
            read (STDIN, buffer, BUFFERSIZE); 

            if (strcmp (buffer, "quit\n") == 0 )
            {    
                printf ("on va quittez le programme merci d'avoir jouer"
                                                        "..........\n");

                plateau_du_jeu.winner = QUIT;
            
                CHECK (send (client1, &plateau_du_jeu, sizeof (display_info),
                                                                         0));
                if (clientsDifferents)
                {
                    CHECK (send (client2, &plateau_du_jeu,
                               sizeof (display_info), 0));
                }
                Finduprogramme = TRUE;
                
                memset (buffer, 0, 8 * sizeof (char));
  
            }
            else if (strcmp (buffer, "restart\n") == 0)
            {
                printf ("la game va restart \n");
                //remettre les variables "essentielles pour la nouvelle partie"
                default_init (&lastjoueur1, &lastjoueur2, &joueur1, &joueur2,
                                    &lightjoueur1, &lightjoueur2, &findugame,
                               &positionDesJoueurs, &plateau_du_jeu, &begin);

                memset (buffer, 0, 8 * sizeof (char));
            }
        }
        if (clientsDifferents)
        {
            if (begin) 
            {
                game_multi_client (client1, client2, &joueur1, &joueur2,
                              &lastjoueur1, &lastjoueur2, &lightjoueur1,
                                     &lightjoueur2, &positionDesJoueurs,
                             &plateau_du_jeu, findugame, &tmp, &lecture,
                             grandSockfd, &timer, refresh_rate, &begin);
            }
        }
        else
        {
            if (begin) 
            {
                game_single_client (client1, &joueur1, &lastjoueur1,
                         &lastjoueur2, &lightjoueur1, &lightjoueur2,
                    &positionDesJoueurs, &plateau_du_jeu, findugame,
                                &tmp, &lecture, grandSockfd, &timer,
                                              refresh_rate, &begin);
            }
        }

        tmp = lecture;
        timer2.tv_sec = 0.5;
    }

    printf ("Le jeu est terminer\n");
    
    // fermeture de la socket
    CHECK (close (client1));
    if (clientsDifferents) CHECK (close (client2));
    CHECK (close (sockfd));


    return 0;

}