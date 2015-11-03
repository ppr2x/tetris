#ifndef PPR2_TETRIS_TETRIS_H
#define PPR2_TETRIS_TETRIS_H

#include "state.h"

void branchFrom(State * state);
int isLeaf(State * state);
void storeBestScore();
void printMap();

#endif //PPR2_TETRIS_TETRIS_H