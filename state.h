#ifndef TETRIS_STATE_H
#define TETRIS_STATE_H

typedef enum {
    EMPTY = 0, SQUARE,
    EL1, EL2, EL3, EL4, EL5, EL6, EL7, EL8,
    STAIRS1, STAIRS2, STAIRS3, STAIRS4,
    TRIANGLE1, TRIANGLE2, TRIANGLE3, TRIANGLE4,
    STICK1, STICK2
} Shape;

typedef struct{
    int index;
    Shape shape;
} State;

State newState(short depth);

void freeState(State state);


#endif //TETRIS_STATE_H
