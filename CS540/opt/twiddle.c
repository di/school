#include <stdio.h>

void twiddle1(int *xp, int *yp)
{
     *xp += *yp;
     *xp += *yp;
}

void twiddle2(int *xp, int *yp)
{
     *xp += 2* *yp;
}

int main(int argc, char *argv[])
{
  int x = 2;
  int y = 3;

  printf("Initial conditions\n");

  printf("x = %d\n",x);
  printf("y = %d\n",y);

  printf("Normal behavior with twiddle1(&x,&y)\n");
  twiddle1(&x, &y);
  printf("x = %d\n",x);
  printf("y = %d\n",y);
  
  x = 2; y = 3;
  twiddle2(&x, &y);
  printf("Normal behavior with twiddle2(&x,&y)\n");
  printf("x = %d\n",x);
  printf("y = %d\n",y);

  printf("Problem with aliasing\n");

  x = 2; y = 3;
  twiddle1(&x, &x);
  printf("Aliased behavior with twiddle1(&x,&x)\n");
  printf("x = %d\n",x);

  x = 2; y = 3;
  printf("Aliased behavior with twiddle2(&x,&x)\n");
  twiddle2(&x, &x);
  printf("x = %d\n",x);

  return 0;
}
