#include <iostream>
#include <fstream>
#include <stdio.h>
#include "level.h"
#include <cstdlib>

using namespace std;

Level::Level(unsigned int& level) {
	sprintf(filename, "level%d.txt", level);

	init();

}

void Level::init() {
	string line;

	moves_so_far = 0;
	is_undo = false;
	is_redo = false;

	ifstream myfile (filename);
	if (myfile.is_open()) {
		getline (myfile,line);
		width = atoi(line.c_str());
		getline (myfile,line);
		high = atoi(line.c_str());
		getline (myfile,line);
		max_moves = atoi(line.c_str());


		for (int i = 0; i < high; i++) {
			getline (myfile,line);
			for (int j = 0; j < width; j++) {
				map[i][j] = line[j];
			}
		}
		myfile.close();
	} else {
		cout << "Unable to load level " << filename;
		system ("pause");
	}
}

sRet Level::validate() {
	//map is done when we don't find any box or spot
	for (int i = 0; i < high; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == SPOT ||
			        map[i][j] == BOX  ||
			        map[i][j] == USSP) {
				if (moves_so_far >= max_moves) {
					return SOKOBAN_EOM;
				} else {
					return SOKOBAN_CONTINUE;
				}
			}
		}
	}
	return SOKOBAN_COMPLETED;
}

sRet Level::draw() {
	bool user_found = false;

	system("cls");

	//center
	unsigned int empty_lines = (SCREEN_HIGH - high) / 2;
	unsigned int empty_rows  = (SCREEN_WIDTH - width) / 2;

	for (int i = 0; i < empty_lines; i++) {
		cout << endl;
	}

	for (int i = 0; i < high; i++) {
		for (int k = 0; k < empty_rows; k++) {
			cout << ' ';
		}
		for (int j = 0; j < width; j++) {

			if (map[i][j] == USSP) {
				cout << USER;
			} else {
				cout << map[i][j];
			}
			if (map[i][j] == USER ||
			        map[i][j] == USSP) {
				if (user_found) {
					return SOKOBAN_NOK;
				}
				cur_x = j;
				cur_y = i;
				user_found == true;
			}
		}
		cout << endl;
	}

	cout << endl << "Moves left: "
	     << max_moves - moves_so_far << endl;

	if (!user_found) {
		return SOKOBAN_NOK;
	}

	return SOKOBAN_OK;
}

sRet Level::moveBox(unsigned int x, unsigned int y) {
	switch (map[y][x]) {
		case SPACE:
			map[y][x] = BOX;
			return SOKOBAN_OK;
		case SPOT:
			map[y][x] = BOXS;
			return SOKOBAN_OK;
		default:
			return SOKOBAN_NOK;
	}
}

void Level::updatePos(unsigned int x, unsigned int y, char next) {
	if (map[cur_y][cur_x] == USSP) {
		map[cur_y][cur_x] = SPOT;
	} else {
		map[cur_y][cur_x] = SPACE;
	}
	if (next == SPACE) {
		map[y][x] = USER;
	} else {
		map[y][x] = USSP;
	}
	cur_x = x;
	cur_y = y;
}


sRet Level::newPos(unsigned int x, unsigned int y) {
	sRet ret;



	switch (map[y][x]) {
		case SPACE:
			updatePos(x, y, SPACE);
			return SOKOBAN_OK;
		case SPOT:
			updatePos(x, y, SPOT);
			return SOKOBAN_OK;
		case BOX:
			ret = moveBox(x + x - cur_x, y + y - cur_y);
			if (ret == SOKOBAN_OK) {
				updatePos(x, y, SPACE);
			}
			return ret;
		case BOXS:
			ret = moveBox(x + x - cur_x, y + y - cur_y);
			if (ret == SOKOBAN_OK) {
				updatePos(x, y, SPOT);
			}
			return ret;
		case WALL:
			//do nothing;
		case USSP:
		case USER:
			//error: double user;
		default:
			//error: unknown field;
			return SOKOBAN_NOK;
	}
}

void Level::do_undo() {
	if (is_undo) {
		memcpy(&redo, &map, sizeof(map));
		memcpy(&map, &undo, sizeof(map));
		moves_so_far--;
		is_undo = false;
		is_redo = true;
	}
}

void Level::do_redo() {
	if (is_redo) {
		memcpy(&undo, &map, sizeof(map));
		memcpy(&map, &redo, sizeof(map));
		moves_so_far--;
		is_undo = true;
		is_redo = false;
	}
}

sRet Level::menu() {
	char option;

	while (true) {

		system("cls");
		cout << "Wybierz opcje:" << endl
		     << "[O]pusc gre" << endl
		     << "[W]roc" << endl
		     << "[R]estart" << endl;

		option = cin.get();
		switch (option) {
			case 'W':
			case 'w':
				return SOKOBAN_NOK;
			case 'R':
			case 'r':
				init();
				return SOKOBAN_NOK;
			case 'O':
			case 'o':
				return SOKOBAN_QUIT;
		}

	}
}

sRet Level::pickMove() {
	char option;
	sRet ret = SOKOBAN_OK;

	cout << "Wybierz kierunek [W ^ | S v | A < | D >]" << endl
	     << "Pozostale opcje: [U]ndo | [R]edo | [M]enu: " << endl;
	option = cin.get();

	memcpy(&temp, &map, sizeof(map));

	switch (option) {
		case 'W':
		case 'w':
			ret = newPos(cur_x, cur_y - 1);
			break;
		case 'S':
		case 's':
			ret = newPos(cur_x, cur_y + 1);
			break;
		case 'A':
		case 'a':
			ret = newPos(cur_x - 1, cur_y);
			break;
		case 'D':
		case 'd':
			ret = newPos(cur_x + 1, cur_y);
			break;
		case 'U':
		case 'u':
			do_undo();
			ret = SOKOBAN_CONTINUE;
			break;
		case 'R':
		case 'r':
			do_redo();
			break;
		case 'M':
		case 'm':
			ret = menu();
			if (ret == SOKOBAN_QUIT) {
				return ret;
			}
			break;
		default:
			return SOKOBAN_NOK;
	}

	if (ret == SOKOBAN_OK) {
		memcpy(&undo, &temp, sizeof(map));
		is_redo = false;
		is_undo = true;
		moves_so_far++;
	}
	
	return ret;
}
