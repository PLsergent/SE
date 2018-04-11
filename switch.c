#include<stdio.h>

void echange(int* p, int* q){
  int tmp;
  printf("Dans la fonction, avant la permutation des variables p=%d q=%d\n",*p,*q);
  tmp = *p;
  *p = *q;
  *q = tmp;
  printf("Dans la fonction, après la permutation des variables p=%d q=%d\n",*p,*q);
}

int main(void){
  int x = 3;
  int y = 5;
  printf("Avant la permutation x=%d y=%d\n",x,y);
  echange(&x,&y);
  printf("Après la permutation x=%d y=%d\n",x,y);

  return 0;
}
