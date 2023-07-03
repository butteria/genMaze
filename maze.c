/*
    Use dfs to generate a maze.
    the output is a byte stream
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* MAZE SIZE */
#define MAZE_TYPE MINI
#define MINI char
#define SMALL short int
#define MEDIUM int
#define BIG long long int

#define _FLAG_WEST_PASS  0b00001000
#define _FLAG_NORTH_PASS 0b00000100
#define _FLAG_EAST_PASS  0b00000010
#define _FLAG_SOUTH_PASS 0b00000001
#define _FLAG_VISITED    0b00010000

/*
    direction bit info:
        11  3 west
        10  2 north
        01  1 east
        00  0 south
*/
const static unsigned char direct_opt[24] =
{
    0xe4, 0xe1, 0xd8, 0xd2, 0xc9, 0xc6,
    0xb4, 0xb1, 0x9c, 0x93, 0x8d, 0x87,
    0x78, 0x72, 0x6c, 0x63, 0x4e, 0x4b,
    0x39, 0x36, 0x2d, 0x27, 0x1e, 0x1b,
};
const static char pos_update[4][2] =
{
    {  1,  0 }, // south
    {  0,  1 }, // east
    { -1,  0 }, // north
    {  0, -1 }, // west
};
const static char flag_updae[4][2] =
{
    { _FLAG_SOUTH_PASS, _FLAG_NORTH_PASS },
    {  _FLAG_EAST_PASS,  _FLAG_WEST_PASS },
    { _FLAG_NORTH_PASS, _FLAG_SOUTH_PASS },
    {  _FLAG_WEST_PASS,  _FLAG_EAST_PASS },
};

unsigned char*
generate_maze(int len, int wid)
{
    int i, j, k;
    unsigned char opt_keys[wid][len];
    unsigned char key;
    unsigned char **maze;
    MAZE_TYPE dig_stack[len * wid][2];
    long long int top = -1;
    long long int cur_y, cur_x, next_y, next_x, cur_dir;

    maze = malloc(sizeof(char*) * wid);
    for(i = 0; i < wid; i++)
    {
        maze[i] = malloc(sizeof(char) * len);
        memset(maze[i], 0, len);
    }

    // random direction options
    srand((unsigned int)time(NULL));
    for(i = 0; i < wid; i++)
        for(j = 0; j < len; j++)
            opt_keys[i][j] = direct_opt[rand() % 24];
    /*
        default startpoint y = 0, x = 0
        ---------> x coordinate(len)
        |
        |
        | y coordinate(wid)
    */
    dig_stack[++top][0] = 0;
    dig_stack[top][1] = 0;
    while(top != -1)
    {
        // get dig position and set visited.
        cur_y = dig_stack[top][0];
        cur_x = dig_stack[top][1];
        maze[cur_y][cur_x] |= _FLAG_VISITED;

        // check dig directions.
        key = opt_keys[cur_y][cur_x];
        do
        {
            cur_dir = key & 0x03;
            key >>= 2;
            if(key == 0x00)
                --top;
            next_y = cur_y + pos_update[cur_dir][0];
            next_x = cur_x + pos_update[cur_dir][1];

            if(next_y < wid && next_x < len && next_y >= 0 && next_x >= 0 &&
                !(maze[next_y][next_x] & _FLAG_VISITED))
            {
                opt_keys[cur_y][cur_x] = key;
                maze[cur_y][cur_x] |= flag_updae[cur_dir][0];
                maze[next_y][next_x] |= flag_updae[cur_dir][1];
                dig_stack[++top][0] = next_y;
                dig_stack[top][1] = next_x;
                break;
            }
        } while(key != 0x00);
    }

    // return bit stream
    k = 0;
    unsigned char *bit_stream = malloc(sizeof(char) * len * wid);
    for(i = 0; i < wid; i++)
    {
        for(j = 0; j < len; j++) {
            bit_stream[k++] = maze[i][j];
        }
    }
    // free memory
    for(i = 0; i < wid; i++)
        free(maze[i]);
    free(maze);
    return bit_stream;
}