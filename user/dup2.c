#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int oldfd = 1, newfd = 3;

    int dup = dup2(oldfd, newfd);

    if (dup2 == -1)
    {
        printf(2, "date failed \n");
        exit();
    }
    printf(1, "El nuevo descriptor %d de fichero copia de %d es %d", oldfd, newfd, dup);
    exit();
}