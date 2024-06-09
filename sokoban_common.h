#ifndef _SOKOBAN_COMMON_H_
#define _SOKOBAN_COMMON_H_

#define WALL  '#'
#define SPOT  '^'
#define USER  '@'
#define BOX   'x'
#define BOXS  'X'
#define SPACE ' '
#define USSP  '$' //user on spot

#define SCREEN_WIDTH 80
#define SCREEN_HIGH  25

typedef enum {
	SOKOBAN_OK,
	SOKOBAN_NOK,
	SOKOBAN_COMPLETED,
	SOKOBAN_QUIT,
	SOKOBAN_CONTINUE,
	SOKOBAN_EOM,
	//zawsze na koncu
	SOKOBAN_MAX,
} sRet;

#endif /* _SOKOBAN_COMMON_H_ */
