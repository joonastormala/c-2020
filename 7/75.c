#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef enum {
    DEAD,
    ALIVE
} CellStatus;

typedef struct {
    unsigned int x_size, y_size;
    CellStatus **cells;
} GameArea;

/* Exercise a: Allocates needed memory for the GameArea structure and
 * the actual game area. 'x_size' and 'y_size' indicate the horizontal and
 * vertical dimensions of the GameArea.
 * 
 * Returns: pointer to the GameArea structure allocated by this function.
 */
GameArea *createGameArea(unsigned int x_size, unsigned int y_size){
    GameArea *ret = malloc(sizeof(GameArea));
    ret->x_size = x_size;
    ret->y_size = y_size;
    ret->cells = malloc(sizeof(CellStatus*) * y_size);
    for(unsigned int i = 0; i<y_size; i++){
        ret->cells[i] = malloc(sizeof(CellStatus) * x_size);
        for(unsigned int j = 0; j<x_size; j++){
            ret->cells[i][j] = DEAD;
        }
    }
    return ret;
}

/* Free memory allocated for GameArea <a>.
 */
void releaseGameArea(GameArea *a){
    for(unsigned int i = 0; i < (a->y_size); i++){
        free(a->cells[i]);
    }
    free(a->cells);
    free(a);
}

/* Exercise b: Initialize game GameArea by setting exactly <n> cells into
 * ALIVE CellStatus in the game GameArea <a>.
 */
void initGameArea(GameArea *a, unsigned int n){
    srand(time(0));
    int x,y;
    unsigned int i = 0;
    while (i != n){
        x=(rand() % a->x_size);
        y=(rand() % a->y_size);
        if(a->cells[y][x] == DEAD){ 
            a->cells[y][x] = ALIVE; 
            i++;
        }  
    }
}

/* Exercise c: Output the current CellStatus of GameArea <a>.
 */
void printGameArea(const GameArea *a){
    for(unsigned int i = 0; i<a->y_size; i++){
        for(unsigned int j = 0; j<a->x_size; j++){
            if(a->cells[i][j]==ALIVE) printf("*");
            else printf(".");
            if(j % a->x_size == a->x_size-1) printf("\n");
        }
    }
}

/* Calculates number of live neighbours around position (x,y),
 * and returns the count.
 */
unsigned int live_neighbours(const GameArea *a, unsigned int x, unsigned int y){
    unsigned int count = 0;
    for(int i = -1; i<=1; i++){
        for(int j = -1; j<=1; j++){
            if(i || j){
                if(((int)x + i >= 0) && (x+i < a->y_size) && ((int)y + j >= 0) && (y+j < a->x_size)){
                    if(a->cells[x+i][y+j] == ALIVE) count++;
                }
            }        
        }
    }
    return count;
}

/* Exercise d: Advance GameArea <a> by one generation.
 */
void gameTick(GameArea *a){
    GameArea *b = createGameArea(a->x_size, a->y_size);
    unsigned int nb = 0;
    for(unsigned int i = 0; i<a->y_size;i++){
        for(unsigned int j = 0; j<a->x_size;j++){
            nb = live_neighbours(a,i,j);
            if(a->cells[i][j] == ALIVE){
                if(nb<2 || nb > 3) b->cells[i][j] = DEAD; else b->cells[i][j] = ALIVE;
            }
            else {
                if(nb == 3) b->cells[i][j] = ALIVE; else b->cells[i][j] = DEAD;
            }
        }
    }
    for(unsigned int i=0;i<(a->y_size);i++){
        memcpy(a->cells[i],b->cells[i],(a->x_size * sizeof(CellStatus)));
    }
    releaseGameArea(b);
}


int main(void)
{
    /* Feel free to modify this function to test different things */
    // re-seed random number generator
    srand((unsigned)time(NULL));

    GameArea *a = createGameArea(50,20);
    initGameArea(a, 150);

    // how many iterations we want
    int rounds = 80;

    // loop iterations, cancel with ctrl-c
    for(int i=0; i<rounds; i++) {
        printf("\nGeneration: %d\n", i+1);
        printGameArea(a);
        // slow down iterations
        sleep(1);
        gameTick(a);
    }
    releaseGameArea(a);
    return 0;
}