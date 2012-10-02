void sub(int *x)
{
    *x = 2;
}

int main(int argc, char *argv[])
{
  int x = 1;

  sub(&x);
  return 0;
}
