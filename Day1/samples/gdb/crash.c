/*
 * Create a core dump - access violation (SIGSEGV)
 * B R Sahu
*/

int main(int argc, char **argv)
{
  char *ptr;

  NulFun(ptr);

  return 0;
}

int NulFun(char *p)
{
  *p = 'A';	/* null pointer derefence */

  return 0;
}

