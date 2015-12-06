#ifndef TETRIS_STACK_H
#define TETRIS_STACK_H

#include "state.h"
#include "tetris.h"
#include <stdio.h>
#include <stdlib.h>

extern int WIDTH, HEIGHT, DEBUG_PARALLEL, my_rank;
extern char ** map;

typedef struct{
    State *state;
    int isBranched;
    void *previous;
    void *next;
} Node;

void stackPrintOut(void);
void stackPrintOutCompact(void);
// Operace na stacku
Node *stackPeek(void);
void stackDeleteTop(void);
State *stackPushState(State* state);
State *stackPushStateWithPoppedInfo(State* state, int isBranched);
int isStackSplittable(void);
int stackSplit(State **states, int half);

int stackSize(void);
int isStackEmpty();

void freeNode(Node *node);

int getArrayFromStackAndMap(int **arr, State *states, int statesCount);
void createStackAndMapFromReceived(int *arr, int dataLength);
void waitForUnfinishedSending(void);

#endif
