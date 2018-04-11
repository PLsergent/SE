#include<stdio.h>

int main(void){
  char a = 'Z';
  int i = 2690;
  float n = 18.217;

  printf("%c %d\n",a,sizeof(a));
  printf("%d %d\n",i,sizeof(i));
  printf("%f %d\n",n,sizeof(n));

  return 0;
}
