// ligne_commande.h

#ifndef _LIGNE_COMMANDE_V2_H
#define _LIGNE_COMMANDE_V2_H

/* La fonction lis_ligne lit sur l'entrée standard une ligne de texte,
 * la decoupe selon les espaces et retourne un tableau de chaînes de caractères (char*)
 * du type attendu par les fonctions execv(3) et execvp(3).
 * Si la fin de fichier est rencontrée, cette fonction retourne NULL.
 */
char** lis_ligne();

/* La fonction fin_de_fichier a en parametre le tableau de chaînes de caractères
 * retourné par la fonction lis_ligne et retourne vrai si lis_ligne a rencontré
 * la fin de fichier, c'est-a-dire si ligne est NULL.
 */
int fin_de_fichier(char** ligne);

/* La fonction ligne_vide a en parametre le tableau de chaînes de caractères
 * retourné par la fonction lis_ligne et retourne vrai si la ligne lue est vide.
 * pré-condition: on n'est pas en fin de fichier, c'est-à-dire ligne != NULL
 */
int ligne_vide(char** ligne);

/* La fonction separe_egal coupe une chaîne de caractères en deux à
 * l'endroit du signe égal, de sorte qu'après son exécution :
 * - la chaine passée en paramètre ne contient plus que sa partie gauche ;
 * - le pointeur retourné pointe vers la partie droite.
 * Si la chaîne passée en paramètre ne contient pas le signe égal, la chaîne
 * n'est pas modifiée et la fonction retourne NULL.
 */
char* separe_egal(char* str);

#endif
