#ifndef TETRIS_STATE_H
#define TETRIS_STATE_H

/************************************************
 * TYPES DEFINITIONS
 ************************************************/
/*
 * ------------------------------------------
 * ------------------------------------------
 * --                  --                  --
 * --   EMPTY is 1x1   --   ##   SQUARE    --
 * --   blank field    --   ##             --
 * --                  --                  --
 * --                  --                  --
 * --                  --                  --
 * ------------------------------------------
 * ------------------------------------------
 * --                  --                  --
 * --      #   EL1     --   #      EL2     --
 * --   ####           --   ####           --
 * --                  --                  --
 * --   ####   EL3     --   ####   EL4     --
 * --      #           --   #              --
 * --                  --                  --
 * --    #     EL5     --   #      EL6     --
 * --    #             --   #              --
 * --    #             --   #              --
 * --   ##             --   ##             --
 * --                  --                  --
 * --   ##     EL7     --   ##     EL8     --
 * --    #             --   #              --
 * --    #             --   #              --
 * --    #             --   #              --
 * --                  --                  --
 * ------------------------------------------
 * ------------------------------------------
 * --                  --                  --
 * --   ##    STAIRS1  --   ##     STAIRS2 --
 * --  ##              --    ##            --
 * --                  --                  --
 * --   #     STAIRS3  --     #    STAIRS4 --
 * --   ##             --    ##            --
 * --    #             --    #             --
 * --                  --                  --
 * ------------------------------------------
 * ------------------------------------------
 * --                  --                  --
 * --  #    TRIANGLE1  --  ###   TRIANGLE2 --
 * -- ###              --   #              --
 * --                  --                  --
 * --                  --                  --
 * --  #    TRIANGLE3  --   #   TRIANGLE4  --
 * --  ##              --  ##              --
 * --  #               --   #              --
 * --                  --                  --
 * ------------------------------------------
 * ------------------------------------------
 * --                  --                  --
 * --  #               --                  --
 * --  #    STICK1     -- #### STICK2      --
 * --  #               --                  --
 * --  #               --                  --
 * --                  --                  --
 * ------------------------------------------
 * ------------------------------------------
 *
 * */

typedef enum {
    EMPTY = 0, SQUARE,
    EL1, EL2, EL3, EL4, EL5, EL6, EL7, EL8,
    STAIRS1, STAIRS2, STAIRS3, STAIRS4,
    TRIANGLE1, TRIANGLE2, TRIANGLE3, TRIANGLE4,
    STICK1, STICK2
} Shape;

/*
 * e.g. for map[3][3]: index = 0, shape = SQUARE
 * | 1|| 1|| 0|
 * | 1|| 1|| 0|
 * | 0|| 0|| 0|
 * */
typedef struct{
    int index;   // Index of top left corner where shape is placed
    Shape shape; // Shape placed at index
} State;


State* newState(int index, Shape shape);
void freeState(State state);


#endif //TETRIS_STATE_H
