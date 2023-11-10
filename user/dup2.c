#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int oldfd = 1, newfd = 3;

    int dup = dup2(oldfd, newfd);

    if (dup == -1)
    {
        printf(2, "date failed \n");
        exit();
    }
    if (newfd == dup)
        printf(1, "El descriptor %d ha sido copiado en el descriptor: %d \n", oldfd, newfd);
    exit();
}