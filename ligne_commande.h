// ligne_commande.h

#ifndef _LIGNE_COMMANDE_V2_H
#define _LIGNE_COMMANDE_V2_H

/* La fonction lis_ligne lit sur l'entr�e standard une ligne de texte,
 * la decoupe selon les espaces et retourne un tableau de cha�nes de caract�res (char*)
 * du type attendu par les fonctions execv(3) et execvp(3).
 * Si la fin de fichier est rencontr�e, cette fonction retourne NULL.
 */
char** lis_ligne();

/* La fonction fin_de_fichier a en parametre le tableau de cha�nes de caract�res
 * retourn� par la fonction lis_ligne et retourne vrai si lis_ligne a rencontr�
 * la fin de fichier, c'est-a-dire si ligne est NULL.
 */
int fin_de_fichier(char** ligne);

/* La fonction ligne_vide a en parametre le tableau de cha�nes de caract�res
 * retourn� par la fonction lis_ligne et retourne vrai si la ligne lue est vide.
 * pr�-condition: on n'est pas en fin de fichier, c'est-�-dire ligne != NULL
 */
int ligne_vide(char** ligne);

/* La fonction separe_egal coupe une cha�ne de caract�res en deux �
 * l'endroit du signe �gal, de sorte qu'apr�s son ex�cution :
 * - la chaine pass�e en param�tre ne contient plus que sa partie gauche ;
 * - le pointeur retourn� pointe vers la partie droite.
 * Si la cha�ne pass�e en param�tre ne contient pas le signe �gal, la cha�ne
 * n'est pas modifi�e et la fonction retourne NULL.
 */
char* separe_egal(char* str);

#endif
