#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "sokoban_common.h"

class Level {
	public:
		Level(unsigned int&);
		sRet draw();
		sRet pickMove();
		sRet validate();

	private:
		sRet newPos(unsigned int x, unsigned int y);
		void updatePos(unsigned int x, unsigned int y, char next);
		sRet moveBox(unsigned int x, unsigned int y);
		void do_undo();
		void do_redo();
		void init();
		sRet menu();
		
		char filename[10];
		char map[100][100];
		char temp[100][100];
		char undo[100][100];
		char redo[100][100];
		bool is_undo;
		bool is_redo;
		unsigned int cur_x;
		unsigned int cur_y;
		unsigned int max_moves;
		unsigned int moves_so_far;
		unsigned int high;
		unsigned int width;
};

#endif /* _LEVEL_H_ */
