#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int x = 10; 
    int *xptr = &x;

    printf("addrr %p\n", &x);
    return EXIT_SUCCESS;
}

