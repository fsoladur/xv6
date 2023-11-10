#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int oldfd = 1, newfd = 4;

    int fd = dup2(oldfd, newfd);

    if (fd == -1)
    {
        printf(2, "date failed \n");
        exit();
    }
    if (newfd == fd)
        printf(1, "El descriptor %d ha sido copiado en el descriptor: %d \n", oldfd, fd);
    exit();
}