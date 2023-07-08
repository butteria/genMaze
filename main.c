#include "maze.h"

int
main()
{
    long long int length, width;
    unsigned char *maze;
    length = width = 10;

    maze = generate(length, width);
    draw_in_terminal(maze, length, width);
    return 1;
}