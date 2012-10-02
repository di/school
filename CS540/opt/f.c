#include <stdio.h>
int counter = 0;

int f(int x)
{
     return counter++;
}

int func1(int x)
{
     return f(x) + f(x) + f(x) + f(x);
}

int func2(int x)
{
     return 4*f(x);
}

int main(int argc, char * argv)
{
     int x = 0;
     printf("func1(x) = %d\n",func1(x));
     counter = 0;
     printf("func2(x) = %d\n",func2(x));
}
