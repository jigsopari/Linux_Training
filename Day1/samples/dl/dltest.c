/*
 * using dynamic loading and unloading
 * gcc -o dltest dltest.c -ldl
 * iBrefore execution: export LD_LIBRARYi_PATH=./
*/

#include <dlfcn.h>
#include <stdio.h>

int main()
{
  void* handle = dlopen("libtest.so", RTLD_LAZY);
  if (handle == NULL)
  {
    printf("%s\n", dlerror());
    return 1;
  }
  void (*test)() = dlsym(handle, "my_function");
  if (test == NULL)
  {
    printf("%s\n", dlerror());
    dlclose(handle);
    return 1;
  }
  (*test)();
  dlclose(handle);

  return 0;
}

