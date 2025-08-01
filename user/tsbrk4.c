#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  char* a = sbrk (15000);

  int pid = fork();

  if(pid != 0){
    wait(NULL);
  }

  a[500] = 1;

  if ((uint)a + 15000 != (uint) sbrk (-15000))
  {
    printf (1, "sbrk() con número positivo falló.\n");
    exit(1);
  }

  if (a != sbrk (0))
  {
    printf (1, "sbrk() con cero falló.\n");
    exit(2);
  }

  if (a != sbrk (15000))
  {
    printf (1, "sbrk() negativo falló.\n");
    exit(3);
  }

  printf (1, "Debe imprimir 1: %d.\n", ++a[500]);

  a=sbrk (-15000);

  a=sbrk(1024*4096*2);

  int pid_2 = fork();

  if(pid_2 != 0)
    wait(NULL);

  a[600*4096*2] = 1;

  sbrk(-1024*4096*2);

  a=sbrk(1024*4096*2);

  printf (1, "Debe imprimir 1: %d.\n", ++a[600*4096*2]);

  exit(0);
}
