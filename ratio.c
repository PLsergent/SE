#include<stdio.h>

typedef struct{
  int numerateur;
  int denominateur;
}ratio;

int main(void){
  ratio r;
  printf("Saisissez un nombre entier positif pour le numérateur : \n");
  scanf("%d",&r.numerateur);
  printf("Saisissez un nombre entier positif pour le dénominateur : \n");
  scanf("%d",&r.denominateur);
}
