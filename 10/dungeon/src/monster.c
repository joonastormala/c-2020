/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}



/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
void moveTowards(const Game *game, Creature *monst) {
    int x = monst->pos.x;
    int y = monst->pos.y;
    if(game->position.x > monst->pos.x) {x++;} else if((game->position.x < monst->pos.x)) {x--;}    
    if(!(isBlocked(game, x,y) || (game->position.x == x && game->position.y == y))){
        monst->pos.x = x;
        return;
    }
    x = monst->pos.x;
    if(game->position.y > monst->pos.y)  {y++;} else if((game->position.y < monst->pos.y)) {y--;}
    if(!(isBlocked(game, x,y) || (x == game->position.x && y == game->position.y))){
        monst->pos.y = y;
        return;
    }
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(const Game *game, Creature *monst) {
    int x = monst->pos.x;
    int y = monst->pos.y;
    (game->position.x > monst->pos.x) ? x-- : x++;
    if(!(isBlocked(game, x,y) || (game->position.x == x && game->position.y == y))){
        monst->pos.x = x;
        return;
        }
    x = monst->pos.x;
    (game->position.y > monst->pos.y) ? y-- : y++;
    if(!(isBlocked(game, x,y) || (game->position.x == x && game->position.y == y))){
        monst->pos.y = y;
        return;
    }
}



/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
	for (unsigned int i = 0; i < game->numMonsters; i++) {
        if(!(game->monsters[i].hp <= 0)){
            double dx = game->monsters[i].pos.x - game->position.x;
            double dy = game->monsters[i].pos.y - game->position.y;
            if(pow(dx,2) + pow(dy,2) < sqrt(2)){
                if(game->monsters[i].attack != 0)
                game->monsters[i].attack(game, &game->monsters[i]);
            } else {
                if(game->monsters[i].move != 0)
                game->monsters[i].move(game, &game->monsters[i]);
            }
        }
    }
}



/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
    unsigned i = 0;
    unsigned tc = sizeof(types) / sizeof(types[0]);
    game->monsters = malloc(sizeof(Creature) * game->opts.numMonsters);
    while (i < game->opts.numMonsters)
    {
        unsigned x = rand() % game->opts.mapWidth;
        unsigned y = rand() % game->opts.mapHeight;
        if (!isBlocked(game, x, y))
        {
            Creature* monst = &game->monsters[i];
            const MonstType* type = types + i % tc;
            monst->hp = type->hplow;
            monst->maxhp = type->hplow;
            strcpy(monst->name, type->name);
            monst->sign = type->sign;
            monst->attack = attackPunch;
            monst->move = moveTowards;
            monst->pos.x = x;
            monst->pos.y = y;
            i++;
            game->numMonsters++;
        } 
    }
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
