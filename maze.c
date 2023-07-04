/*
    Use dfs to generate a maze.
    the output is a byte stream
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* MAZE SIZE */
#define MAZE_TYPE SMALL
#define MINI char
#define SMALL short int
#define MEDIUM int
#define BIG long long int

#define _FLAG_VISITED    0x10
#define _FLAG_WEST_PASS  0x08
#define _FLAG_NORTH_PASS 0x04
#define _FLAG_EAST_PASS  0x02
#define _FLAG_SOUTH_PASS 0x01
#define _DIR_WEST        3
#define _DIR_NORTH       2
#define _DIR_EAST        1
#define _DIR_SOUTH       0

signed char direct_opt[24] =
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
        Space: ( 2 * (unsigned char)N^2 + (MAZE_TYPE)N^2 )
    */
    int i;
    long long int size = width * length;
    long long int top = -1;
    unsigned char key, dir;
    long long int cur_yx, next_yx;
    unsigned char *opt_keys = NULL;
    MAZE_TYPE *dig_stack = NULL;
    unsigned char *maze = NULL;

    maze = malloc(sizeof(unsigned char) * size);
    opt_keys = malloc(sizeof(unsigned char) * size);
    dig_stack = malloc(sizeof(MAZE_TYPE) * size);
    memset(maze, 0, size);

    // random direction options
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

    long long int lines = width * 2 - 1;
    int j;
    printf(" --");
    for(j = 1; j < length; j++)
        printf("---");
    printf("\n");
    for(i = 1; i <= lines; i++)
    {
        if(i % 2)
        {
            for(j = 0; j < length; j++)
                maze[(i>>1) * length + j] & _FLAG_WEST_PASS ? printf("   ") : printf("|  ");
        }
        else {
            maze[(i>>1) * length] & _FLAG_NORTH_PASS ? printf("   ") : printf(" --");
            for(j = 1; j < length; j++)
                maze[(i>>1) * length + j] & _FLAG_NORTH_PASS ?  printf("   ") : printf("---");
        }
        printf("|  \n");
    }
    printf(" --");
    for(j = 1; j < length; j++)
        printf("---");

    free(opt_keys);
    free(dig_stack);
    return maze;
}
 int main()
 {
    unsigned char *ret;
    int width = 5, length = 5;
    int size = width * length;
    ret = generate(length, width);
 }