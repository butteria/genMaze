#include <stdio.h>
#include "ascii.h"

int
main(int argc, char *argv[])
{
    char str[10];
    while(gets(str))
        convert2block(str);
    return 1;
}