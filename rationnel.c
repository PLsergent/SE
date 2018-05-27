/* auteur : Isabelle DAUTRAIX */
/* sujet : programme qui demande la saisie au clavier d'un rationnel positif puis qui affiche le
 * rationnel simplifi�.
 */

#include <stdio.h> // scanf, printf

// structure de donn�es pour mod�liser un rationnel
typedef struct
{
    int numerateur;
    int denominateur;
}Rationnel;

int pgcd(int*,int*);
void simplification(Rationnel*);

int main(void)
{
   Rationnel rationnel;

   // saisie du rationnel positif
   printf("Veuillez, s'il vous plait, saisir un nombre rationnel positif.\n");
   do
   {
       printf("numerateur   (entier             positif) = ");
       scanf("%d",&rationnel.numerateur); // les parenth�ses ne sont pas obligatoires car l'op�rateur . est prioritaire sur l'op�rateur &
   }while(rationnel.numerateur<0);
   do
   {
       printf("denominateur (entier strictement positif) = ");
       scanf("%d",&rationnel.denominateur);
   }while(rationnel.denominateur<=0);

   // affichage du rationnel simplifi�
   if (rationnel.numerateur==0) // les parenth�ses ne sont pas obligatoires car l'op�rateur . est prioritaire sur l'op�rateur ==
      printf("rationnel simplifie = 0");
   else
   {
      simplification(&rationnel);
      if (rationnel.denominateur==1)
         printf("rationnel simplifie = %d",rationnel.numerateur);
      else
         printf("rationnel simplifie = %d / %d\n",rationnel.numerateur,rationnel.denominateur);
   }

   return 0;
}

// fonction qui a en param�tre deux entiers strictement positifs et qui calcule puis renvoie le Plus Grand Commun Diviseur de ces nombres
int pgcd(int *n,int *d)
{
   int calcul;

   if (*n<*d)
      calcul=*n;
   else
      calcul=*d;

   while(*n%calcul!=0 || *d%calcul!=0)
       calcul--;

   return calcul;
}

// fonction qui a en param�tre un rationnel et qui calcule puis renvoie le rationnel simplifi�
void simplification(Rationnel* fraction)
{
    int pgcd_calcule = pgcd(&fraction->numerateur, &fraction->denominateur);
    fraction->numerateur = fraction->numerateur / pgcd_calcule;
    fraction->denominateur = fraction->denominateur / pgcd_calcule;
}
