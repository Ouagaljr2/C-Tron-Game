#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

#include "common.h"


/**
 * @brief initialise le tableau 2d board avec la caractère '*' et les bords du
 * tableau à WALL (111)
 * 
 * @param board 
 */
void my_window_init (char board[XMAX][YMAX]);

/**
 * @brief parcourt le tableau 2d board et dessine aux cordonnées dont l'élement
 * est different de '*' soit 'X' pour 0 'Z' pour 1 un carré rouge pour 50 et
 * bleue pour 51 et pour 111 des lignes verticales et horizontales pour les
 * bordures
 * 
 * @param board 
 */
void my_draw_window (char board[XMAX][YMAX]);

/**
 * @brief initialise la structure players_position positions à des valeurs
 * entieres aléatoires
 * 
 * @param positions 
 */
void initPosition (players_position * position);

/**
 * @brief génère un nombre aléatoire dans l'intervalle min,max
 * 
 * @param min 
 * @param max 
 * @return retourne l'entier aléatoire généré
 */
int my_random (int min, int max);

/**
 * @brief deplacement aux coordonnées actuelles plus le nouveau input pour les
 * deux joueurs la tete si ce deplacement ne creer pas une collision
 * 
 * @param input 
 * @param positionDesJoueurs 
 * @param plateau_du_jeu 
 * @param id 
 * @param light 
 * @return TRUE ( 1 ) si ce deplacement creer une collision FALSE ( 0 ) si non
 */
int movement_multi_client (char input, players_position * positionDesJoueurs,
                           display_info * plateau_du_jeu, int id, int light);

/**
 * @brief deplacement aux coordonnées actuelles plus le nouveau input pour
 * le joueur la tete si ce deplacement ne creer pas une collision
 * 
 * @param input 
 * @param positionDesJoueurs 
 * @param plateau_du_jeu 
 * @param light 
 * @return TRUE ( 1 ) si ce deplacement creer une collision FALSE ( 0 ) si non
 */
int movement_single_client (char input, players_position * positionDesJoueurs,
                                    display_info * plateau_du_jeu, int light);


/**
 * @brief détermine s'il y une collision pour le joueur d'id id aux cordonnées x et y dans le champ borad
 * de la structure display_info plateau_du_jeu
 * 
 * @param plateau_du_jeu 
 * @param x 
 * @param y 
 * @param id 
 * @return TRUE ( 1 ) s'il ya une collision FALSE( 0 )  si non
 */
int collision (display_info * plateau_du_jeu, int x, int y, int id);

/**
 * @brief détermine s'il y a un gagnant
 * 
 * @param plateau_dujeu 
 * @return TRUE ( 1 ) si oui FALSE ( 0 ) si non
 */
int winner (display_info plateau_dujeu);

/**
 * @brief dessine (affiche) le vainqueur de la partie d'id winnerid
 * 
 * @param board 
 * @param winnerid 
 */
void draw_winner (char board[XMAX][YMAX], int winnerid);

/**
 * @brief creer la socket pour le serveur
 * 
 * @param port 
 * @param adrIP 
 * @param my_addr 
 * @return la socket du serveur
 */
int sock_server (int port, char * adrIP, SAI * my_addr);

/**
 * @brief creer la socket du client
 * 
 * @param port 
 * @param adrIP 
 * @param my_addr 
 * @return la socket du client
 */
int sock_client (int port, char * adrIP, SAI * my_addr);

/**
 * @brief gere le jeu pour un seul client avec deux joueurs detecte
 * les mouvements calcul les collisions et effectue les deplacements
 * 
 * @param client1 
 * @param joueur1 
 * @param lastjoueur1 
 * @param lastjoueur2 
 * @param lightjoueur1 
 * @param lightjoueur2 
 * @param positionDesJoueurs 
 * @param plateau_du_jeu 
 * @param findugame 
 * @param tmp 
 * @param lecture 
 * @param grandSockfd 
 * @param timer 
 * @param refresh_rate 
 * @param begin 
 */
void game_single_client (int client1, struct client_input *joueur1,
                              char *lastjoueur1, char *lastjoueur2,
                              int *lightjoueur1, int *lightjoueur2,
                             players_position * positionDesJoueurs,
                      display_info * plateau_du_jeu, int findugame,
                     fd_set *tmp, fd_set* lecture, int grandsockfd,
           struct timeval * timer, int refresh_rate, int * begin );


/**
 * @brief gere le jeu pour un deux clients avec chacun un joueur detecte 
 * les mouvements calcul les collisions et effectue les deplacements
 * 
 * @param client1 
 * @param client2 
 * @param joueur1 
 * @param joueur2 
 * @param lastjoueur1 
 * @param lastjoueur2 
 * @param lightjoueur1 
 * @param lightjoueur2 
 * @param positionDesJoueurs 
 * @param plateau_du_jeu 
 * @param findugame 
 * @param tmp 
 * @param lecture 
 * @param grandSockfd 
 * @param timer 
 * @param refresh_rate 
 * @param begin 
 */
void game_multi_client (int client1, int client2, struct client_input *joueur1,
                              struct client_input * joueur2, char *lastjoueur1, 
                       char *lastjoueur2, int *lightjoueur1, int *lightjoueur2, 
                                         players_position * positionDesJoueurs,
                                  display_info * plateau_du_jeu, int findugame,
                                 fd_set *tmp, fd_set* lecture, int grandSockfd,
                        struct timeval * timer, int refresh_rate, int * begin);


/**
 * @brief met tous les arguments à leur valeurs initialles pour commencer
 * une nouvelle partie
 * 
 * @param lastjoueur1 
 * @param lastjoueur2 
 * @param joueur1 
 * @param joueur2 
 * @param lightjoueur1 
 * @param lightjoueur2 
 * @param findugame 
 * @param positionDesJoueurs 
 * @param plateau_du_jeu 
 * @param begin 
 */
void default_init (char *lastjoueur1, char * lastjoueur2,
                            struct client_input *joueur1, 
                            struct client_input *joueur2,
                    int *lightjoueur1, int *lightjoueur2,
                                         int * findugame,
                   players_position * positionDesJoueurs,
             display_info * plateau_du_jeu, int * begin);





#endif