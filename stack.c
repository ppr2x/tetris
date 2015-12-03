#include "stack.h"

#define NULL_NODE (Node *)0

int size = 0;

Node *stackTop = NULL_NODE;
Node *stackBottom = NULL_NODE;

void stackPrintOut(void){
    if(isStackEmpty()){printf("\nStack is empty.\n"); return;}
    Node *node = stackBottom;
    printf("--- Stack bottom\n");
    while(node != NULL_NODE){
        printf("depth - %d, isBranched - %d, index - %d, shape - %d\n", node->state->depth, node->isBranched, node->state->index, node->state->shape);
        node = node->next;
    }
    printf("--- Stack top\n\n");
}

void stackPrintOutCompact(void){
    if(isStackEmpty()){printf("\nStack is empty.\n"); return;}
    printf("---> Stack contents (index,shape)\n");
    Node *node = stackBottom;
    while(node != NULL_NODE){
        printf("(%d,%d,d%d),", node->state->index, node->state->shape, node->state->depth);
        node = node->next;
    }
    printf(";TOP\n");
}

Node *stackPeek(void){
    return stackTop;
}

void stackDeleteTop(void){
    if(stackTop==NULL_NODE){return;}
    Node *previous = stackTop->previous;
    free(stackTop->state);
    freeNode(stackTop);
    stackTop = previous;
    if(stackTop != NULL_NODE){
        stackTop->next = NULL_NODE;
    }
    size--;
}

State *stackPushState(State* state){
    return stackPushStateWithPoppedInfo(state, 0);
}

State *stackPushStateWithPoppedInfo(State* currentState, int isBranched){
    Node *currentNode = (Node *)malloc(sizeof(Node));
    if(currentNode == NULL){printf("Out of memory during push!"); exit(EXIT_FAILURE);}

    if(size > 0){ // stack neni prazdny -> navazat
        stackTop->next = currentNode;
        currentNode->previous = stackTop;
    } else { // stack je prazdny -> nastavit dno
        stackBottom = currentNode;
        currentNode->previous = NULL_NODE;
    }

    currentNode->next = NULL_NODE; // je vrchol
    currentNode->state = currentState;
    currentNode->isBranched = isBranched;

    stackTop = currentNode;
    size++;

    return currentState;
}

int isStackSplittable(void){
    if(isStackEmpty()){
        //printf("(%d) Stack is empty.\n", rank);
        return 0;
    }

    Node *node = stackBottom;
    while(node->isBranched){
        node = node->next;
        if(node == NULL_NODE){
            //printf("(%d) Stack contains only branched nodes.\n", rank);
            return 0;
        }
    }
    return 1;
}

/*
 * Split the stack with D-ADZ method (half at the bottom)
 * Take unpopped nodes from bottom to last unpopped, split in half,
 * save to **states and repair stack
 */
int stackSplit(State **states, int half) {
    if(!isStackSplittable()) return 0;

    Node *node = stackBottom;
    while(node->isBranched){
        node = node->next;
        if(node == NULL_NODE){
            //printf("(%d) Stack contains only branched nodes.\n", rank);
            return 0;
        }
    }

    // Count total number of cuttable nodes
    int cuttableNodeDepth = node->state->depth;
    int cuttableNodeCount = 0;
    do {
        cuttableNodeCount++;
        node = node->next;
    } while(node->state->depth == cuttableNodeDepth && !node->isBranched);

    // Cut in half (+1)
    int nodesToCutCount = half ? (cuttableNodeCount + 1) / 2 : 1;
    if (cuttableNodeCount > 0 && nodesToCutCount > 0) {
        *states = (State *)malloc(nodesToCutCount * sizeof(State));
        if(*states == NULL){
            printf("Out of memory during stack cutting!");
            exit(EXIT_FAILURE);
        }

        Node *firstUncutNode = node;
        node = node->previous;

        // Free nodes
        int i;
        Node *previous;
        for (i = 0; i < nodesToCutCount; i++) {
            (*states)[i] = *node->state;
            previous = node->previous;

            //TODO free what is to be freed, but allow sending of data
            freeNode(node);
            node = previous;
        }
        size -= nodesToCutCount; // Reduce stack size counter

        // Repair stack
        node->next = firstUncutNode;
        firstUncutNode->previous = node;
        return nodesToCutCount;
    }
    return 0;
}

int stackSize(void){
    return size;
}

int isStackEmpty(){
    return (stackSize()==0)?1:0;
}

void freeNode(Node *node){
    free(node);
}

int getArrayFromStackAndMap(int **arr, State *states, int statesCount){
    if(statesCount <= 0){return 0;}
    int stateLen = 3, i;
    int mapLen = WIDTH * HEIGHT;
    int size = mapLen + stateLen * statesCount;

    // Get serialized map
    int * mapToSerialize = (int*)malloc(mapLen*sizeof(int));
    int * statesToSerialize = (int*)malloc(stateLen*statesCount*sizeof(int));
    copyMapToIntArray(mapToSerialize, map);

    // Get serialized states
    int counter = 0, *counter_p = &counter;
    State * state = states;
    for(i=0;i<statesCount;i++){
        getArrayFromState(statesToSerialize, state++, counter_p);
    }

    // Save to arr
    for(i=0;i<mapLen;i++){
        arr[i] = mapToSerialize+i;
    }
    for(i=0;i<size-mapLen;i++){
        arr[mapLen+i] = statesToSerialize+i;
    }

    return size;
}

void createStackAndMapFromReceived(int *arr, int dataLength) {
    int i,j, counter = 0;

    // Init stack
    stackTop = NULL_NODE;
    stackBottom = NULL_NODE;

    // Parse & create map
    map = newMap();
    for(i=0;i<WIDTH;i++){
        for(j=0;j<HEIGHT;j++){
            map[i][j] = (char) *(arr+counter);
            counter++;
        }
    }
    // Parse & push states
    while(counter < dataLength) {
        State s = getStateFromArray(arr, &counter);
        stackPushState(&s);
    }
}