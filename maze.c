/*
    Use dfs to generate a maze.
    the output is a byte stream
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze.h"

const unsigned char direct_opt[24] =
{
    0xe4, 0xe1, 0xd8, 0xd2, 0xc9, 0xc6,
    0xb4, 0xb1, 0x9c, 0x93, 0x8d, 0x87,
    0x78, 0x72, 0x6c, 0x63, 0x4e, 0x4b,
    0x39, 0x36, 0x2d, 0x27, 0x1e, 0x1b,
};
static char pos_update[4] =
{
     0, // south
     1, // east
     0, // north
    -1, // west
};
const static unsigned char flag_updae[4][2] =
{
    { _FLAG_SOUTH_PASS, _FLAG_NORTH_PASS },
    {  _FLAG_EAST_PASS,  _FLAG_WEST_PASS },
    { _FLAG_NORTH_PASS, _FLAG_SOUTH_PASS },
    {  _FLAG_WEST_PASS,  _FLAG_EAST_PASS },
};

unsigned char*
generate(long long int length, long long int width)
{   /*
        Time: ( N^2 )
        Space: ( 3 * (unsigned char)N^2 + (MAZE_TYPE)N^2 )
    */
    int i;
    long long int size = width * length;
    long long int top = -1;
    unsigned char key, dir;
    long long int cur_yx, next_yx;
    unsigned char *opt_keys , *limit_dirs, *maze;
    MAZE_TYPE *dig_stack;

    maze = malloc(sizeof(unsigned char) * size);
    opt_keys = malloc(sizeof(unsigned char) * size);
    limit_dirs = malloc(sizeof(unsigned char) * size);
    dig_stack = malloc(sizeof(MAZE_TYPE) * size);
    memset(maze, 0, size);

    // set direction limitations.
    memset(limit_dirs, 0, size);
    for(i = 0; i < length; i++)
        limit_dirs[i] |= _LIMIT_DIR_NORTH;
    for(i = 0; i < length; i++)
        limit_dirs[size - 1 - i] |= _LIMIT_DIR_SOUTH;
    for(i = 0; i < size; i += length)
        limit_dirs[i] |= _LIMIT_DIR_WEST;
    for(i = length - 1; i < size; i += length)
        limit_dirs[i] |= _LIMIT_DIR_EAST;

    // random direction options.
    srand((unsigned int)time(NULL));
    for(i = 0; i < size; i++)
            opt_keys[i] = direct_opt[rand() % 24];
    pos_update[0] = length;
    pos_update[2] = -length;
    /*
        default startpoint y = 0, x = 0
        ---------> x coordinate(length)
        |
        |
        | y coordinate(width)
    */
    dig_stack[++top] = 0;
    while(top != -1)
    {
        // get dig position and set visited.
        cur_yx = dig_stack[top];
        maze[cur_yx] |= _FLAG_VISITED;

        // check dig directions.
        key = opt_keys[cur_yx];
        do
        {
            dir = key & 0x03;
            key >>= 2;
            if(key == 0x00)
                --top;
            // check direction limitations ?
            if(limit_dirs[cur_yx] >> dir & 0x01)
                continue;

            next_yx = cur_yx + pos_update[dir];
            if(next_yx >= 0 && next_yx < size && !(maze[next_yx] & _FLAG_VISITED))
            {
                opt_keys[cur_yx] = key;
                maze[cur_yx] |= flag_updae[dir][0];
                maze[next_yx] |= flag_updae[dir][1];
                dig_stack[++top] = next_yx;
                break;
            }
        } while(key != 0x00);
    }

    free(opt_keys);
    free(dig_stack);
    return maze;
}

void
draw_in_terminal(unsigned char *maze, long long int length, long long int width)
{
    long long int y, x, lines;

    printf("+---");
    for(x = 1; x < length; x++)
        printf("----");
    printf("+\n");
    for(lines = 1; lines < width << 1; lines++)
    {
        y = (lines >> 1) * length;
        // draw vertical wall.
        if(lines % 2)
        {
            for(x = 0; x < length; x++)
                maze[y + x] & _FLAG_WEST_PASS ? printf("    ") : printf("|   ");
        }
        else {
            // draw horizontal wall.
            maze[y] & _FLAG_NORTH_PASS ? printf("|   ") : printf("|---");
            for(x = 1; x < length; x++)
            {
                if(maze[y - length + x] & _FLAG_WEST_PASS && maze[y + x] & _FLAG_WEST_PASS)
                    printf("-");
                else if(!(maze[y - 1 + x] & _FLAG_NORTH_PASS) && !(maze[y + x] & _FLAG_NORTH_PASS))
                    printf("-");
                else if(maze[y - 1 + x] & _FLAG_NORTH_PASS && maze[y + x] & _FLAG_NORTH_PASS)
                    printf("|");
                else if(!(maze[y - length + x] & _FLAG_WEST_PASS) && !(maze[y + x] & _FLAG_WEST_PASS))
                    printf("|");
                else
                    printf("+");
                maze[y + x] & _FLAG_NORTH_PASS ? printf("   ") : printf("---");
            }
        }
        printf("|\n");
    }
    printf("+---");
    for(x = 1; x < length; x++)
        printf("----");
    printf("+\n");
}