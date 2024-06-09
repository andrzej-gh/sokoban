#ifndef _LEVELS_H_
#define _LEVELS_H_

#define WIDTH 9
#define HIGH  9

typedef struct Level {
	unsigned int width;
	unsigned int high;
	unsigned int start_x;
	unsigned int start_y;
	unsigned int max_moves;
	unsigned int moves_so_far;
	char **level;
} Level;

char level[1][HIGH][WIDTH] = {
{
	{' ', ' ', '#', '#', '#', '#', '#', ' ', ' '},
	{'#', '#', '#', ' ', ' ', ' ', '#', ' ', ' '},
	{'#', '^', '@', 'x', ' ', ' ', '#', ' ', ' '},
	{'#', '#', '#', ' ', 'x', '^', '#', ' ', ' '},
	{'#', '^', '#', '#', 'x', ' ', '#', ' ', ' '},
	{'#', ' ', '#', ' ', '^', ' ', '#', '#', ' '},
	{'#', 'x', ' ', 'X', 'x', 'x', '^', '#', ' '},
	{'#', ' ', ' ', ' ', '^', ' ', ' ', '#', ' '},
	{'#', '#', '#', '#', '#', '#', '#', '#', ' '},
},
};

#endif /* _LEVELS_H_ */
