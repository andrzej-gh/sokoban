#include <iostream>
#include "sokoban.h"
#include "level.h"

using namespace std;

Sokoban::Sokoban() {
	cur_level = 0;
	max_done  = 0;
	max_level = 1;
}

sRet Sokoban::startNewGame() {
	sRet ret;
	Level level(cur_level);

	while (true) {
		level.draw();
		ret = level.pickMove();
		if (ret == SOKOBAN_QUIT) {
			return ret;
		}
		ret = level.validate();
		if (ret != SOKOBAN_CONTINUE) {
			return ret;
		}
	}
}

void Sokoban::showEntry () {
	cout << "Sokoban version -1.0" << endl
	     << "Autor: Nieznany" << endl << endl;

	system("pause");
}

void Sokoban::pickLevel() {
	if (max_done > 0) {
		while (true) {
			system ("cls");
			cout << "Wybierz Poziom [0-"
			     << max_done << "]: ";
			cin >> cur_level;
			if (cur_level <= max_done) {
				return;
			}
		}
	}
}

void Sokoban::play() {
	char option;
	bool continue_game;
	sRet ret;

    pickLevel();

	while (true) {
		ret = startNewGame();
		while (true) {
			system("cls");
			if (ret == SOKOBAN_COMPLETED) {
				if (cur_level == max_level) {
					cout << "You finished the game!" << endl;
					system("pause");
					return;
				}
				max_done++;
				cout << "You completed level "
				     << cur_level << "!" << endl
				     << "Do you want to continue [y/n]?";
			} else if (ret == SOKOBAN_QUIT) {
				return;
			} else {
				cout << "You lose!" << endl
				     << "Again [y/n]?";
			}
			option = cin.get();
			switch (option) {
				case 'Y':
				case 'y':
					if (SOKOBAN_COMPLETED) {
						cur_level++;
					}
					continue_game = true;
					break;
				case 'N':
				case 'n':
					return;
			}
			if (continue_game) {
				break;
			}

		}
	}
}

void Sokoban::showMenu() {
	char option = ' ';
	sRet ret;
	while (true) {
		system("cls");
		cout << "Menu" << endl
		     << "[N]owa Gra," << endl
		     << "[W]yjscie." << endl
		     << endl
		     << "Wybierz opcje: ";
		option = cin.get();

		switch (option) {
			case 'N':
			case 'n':
				play();
				break;
			case 'W':
			case 'w':
				return;
		}
	}
}
