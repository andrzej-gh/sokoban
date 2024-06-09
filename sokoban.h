#ifndef _SOKOBAN_H_
#define _SOKOBAN_H_

#include "sokoban_common.h"

class Sokoban {
	public:
		Sokoban();
		void showEntry();
		void showMenu();

	private:
		sRet startNewGame();
		void pickLevel();
		void play();
		//Obecny poziom gry:
		unsigned int cur_level;
		unsigned int max_level;
		unsigned int max_done;
		unsigned int cur_x;
		unsigned int cur_y;
		//Level levels [max_level];

};

#endif /* _SOKOBAN_H_ */
