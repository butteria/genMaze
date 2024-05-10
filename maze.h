#ifndef MAZE_H
#define MAZE_H

/* MAZE SIZE */
#define MAZE_TYPE SMALL
#define MINI char
#define SMALL short int
#define MEDIUM int
#define BIG long long int

/* BIT FLAG INFO */
#define _FLAG_VISITED    0x10
#define _FLAG_WEST_PASS  0x08
#define _FLAG_NORTH_PASS 0x04
#define _FLAG_EAST_PASS  0x02
#define _FLAG_SOUTH_PASS 0x01
#define _LIMIT_DIR_WEST  0x08
#define _LIMIT_DIR_NORTH 0x04
#define _LIMIT_DIR_EAST  0x02
#define _LIMIT_DIR_SOUTH 0x01

unsigned char* generate(long long int length, long long int width);
void draw_in_terminal(unsigned char *maze, long long int length, long long int width);

#endif