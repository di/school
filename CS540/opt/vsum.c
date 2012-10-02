#define MAX 1000

int a[MAX], b[MAX], c[MAX];

// Vector sum version 1.
// Input and output vectors are global

void vsum1(int n)
{
     int i;

     for (i = 0; i < n; i++)
       c[i] = a[i] + b[i];
}

// Vector sum version 2.  Unrolled by by 2.  
// Input and output vectors are global
// Assume that n is even.

void vsum2(int n)
{
     int i;

     for (i = 0; i < n; i+=2) {
       c[i] = a[i] + b[i];
       c[i+1] = a[i+1] + b[i+1];
     }
}
