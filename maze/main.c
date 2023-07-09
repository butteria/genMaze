#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

int
main(int argc, char *argv[])
{
    long long int length = 10, width = 10;
    unsigned char *maze;

    const char *optstring = "l:w:h";
    int option_index = 0;
    int opt;

    static struct option long_options[] =
    {
       { "length", required_argument, NULL, 'l' },
       {  "width", required_argument, NULL, 'w' },
       {   "help",       no_argument, NULL, 'h' },
       {        0,                 0,    0,  0  },
    };

    while( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
    {
        switch(opt)
        {
            case 'l':
                length = atoi(optarg);
                break;
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                printf("--length -l\tspecify the length of maze.\n");
                printf("--width -w\tspecify the width of maze.\n");
                return 1;
                break;
            default :
                printf("invalid options.\n");
                return 0;
                break;
        }
    }

    maze = generate(length, width);
    draw_in_terminal(maze, length, width);
    return 1;
}