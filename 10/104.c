#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/********************************************************
 * NOTE: THIS IS SAME AS DUNGEON FOLDER BUT IN ONE FILE *
 ********************************************************/

// Pair of coordinates in the 2-dimensional map
typedef struct {
	int x, y;
} Point;

// Room information. Used only in map creation
typedef struct {
	int x1, x2, y1, y2;
	unsigned int w, h;
	Point center;
} Room;

// Different tile types
typedef enum {
	TILE_OPEN,  // can be moved to
	TILE_WALL,  // cannot be moved to
	TILE_ROOM   // can be moved to
} Tile;

// 2-dimensional dynamically allocated array for the game map
// Dimensions are given in Options struct (mapWidth, mapHeight)
typedef struct {
    Tile **tile;   // tile[y][x]
} Map;

// Global game options
typedef struct {
    unsigned int numRooms;  // number of rooms on the map
    unsigned int minRoomSize;  // minimum size (diameter) of a room
    unsigned int maxRoomSize;  // maximum size (diameter) of a room
    unsigned int mapWidth;  // map width
    unsigned int mapHeight;  // map height
    unsigned int numMonsters;   // number of monster generated on map
    unsigned int visibility;  // number of squares that player sees
    int showAll;  // if 1, show the full map to player, if 0 show just 'visibility' squares
} Options;

typedef struct game_st Game;

// Monster information
typedef struct creature_st {
    char name[20];  // name of the monster
    char sign;  // character that represents monster on the game display
    Point pos;  // location of the monster
    float hp;  // current hitpoints
    unsigned int maxhp;  // maximum hitpoints
    void (*move)(const Game *, struct creature_st *);  // current movement algorithm for monster
    void (*attack)(Game *, struct creature_st *);  // current attack algorithm for monster
} Creature;

// Global data for the game
struct game_st {
    Map map;
    unsigned int numMonsters;  // number of elements in 'monsters' array
    Creature *monsters;  // dynamic array of all monsters
    Point position;  // current position of the player
    float hp;  // hit points, should never be higher than 'maxhp'
    unsigned int maxhp;  // maximum hit points
    Options opts;
};


/* Public functions in mapgen.c */
void generateMap(Game *game);
void freeAll(Game *game);

/* Public functions in userif.c */
int doCommand(Game *game, char *buf);
int isBlocked(const Game *game, int x, int y);
void printMap(const Game *game);
void showMap(const Game *game);

/* Public functions in monster.c */
void createMonsters(Game *game);
void monsterAction(Game *game);
void checkIntent(Game *game);
void moveTowards(const Game *game, Creature *monst);
void moveAway(const Game *game, Creature *monst);
void attackPunch(Game *game, Creature *monst);

/* Initialize a new room, with given coordinates (x,y) and dimensions (w,h)
 */
void newRoom(Room *nr, int x, int y, unsigned int w, unsigned int h) {
    nr->x1 = x;
    nr->x2 = x + w;
    nr->y1 = y;
    nr->y2 = y + h;
    nr->center.x = (nr->x1 + nr->x2) / 2;
    nr->center.y = (nr->y1 + nr->y2) / 2;
}

/* returns 0 if the two given rooms do not overlap, non-zero otherwise
 */
int intersects(const Room *a, const Room *b) {
    return (a->x1 <= b->x2 &&
            a->x2 >= b->x1 &&
            a->y1 <= b->y2 &&
            a->y2 >= b->y2);
}

/* Initialize the map data for a given room
 */
void initRoom(Room *nr, Map *m) {
    for (int i = nr->y1; i < nr->y2; i++) {
        for (int j = nr->x1; j < nr->x2; j++) {
            m->tile[i][j] = TILE_ROOM;
        }
    }
}

/* set up a horizontal corridor at given coordinates
 */
void hCorridor(Map *map, int x1, int x2, int y) {
    int minx = (x1 < x2 ? x1 : x2);
    int maxx = (x1 < x2 ? x2 : x1);

    for (int x = minx; x <= maxx; x++) {
        map->tile[y][x] = TILE_OPEN;
    }
}

/* Set up a vertical corridor at given coordinates
 */
void vCorridor(Map *map, int y1, int y2, int x) {
    int miny = (y1 < y2 ? y1 : y2);
    int maxy = (y1 < y2 ? y2 : y1);

    for (int y = miny; y <= maxy; y++) {
        map->tile[y][x] = TILE_OPEN;
    }
}

/* Draw corridors between two rooms
 * Start randomly either to horizontal direction or vertical direction
 */
void drawCorridors(Map *m, Room *a, Room *b) {
    if (rand() & 1) {
        hCorridor(m, a->center.x, b->center.x, a->center.y);
        vCorridor(m, a->center.y, b->center.y, b->center.x);
    } else {
        vCorridor(m, a->center.y, b->center.y, a->center.x);
        hCorridor(m, a->center.x, b->center.x, b->center.y);
    }
}

/* Place rooms on the map and create corridors between them
 */
void placeRooms(Game *game) {
    Map *map = &game->map;
    Options *opt = &game->opts;
    Room *rooms;
    rooms = malloc(sizeof (Room) * opt->numRooms);
    if (!rooms) {
        // No use going on
        exit(EXIT_FAILURE);
    }
        
    int failed = 1;
    for (unsigned int i = 0; i < opt->numRooms; i++) {
        do {
            unsigned int w = opt->minRoomSize + rand() % (opt->maxRoomSize - opt->minRoomSize);
            unsigned int h = opt->minRoomSize + rand() % (opt->maxRoomSize - opt->minRoomSize);
            int x = rand() % (opt->mapWidth - w - 1) + 1;
            int y = rand() % (opt->mapHeight - h - 1) + 1;
            newRoom(&rooms[i], x, y, w, h);

            failed = 0;
            for (unsigned int j = 0; j < i; j++) {
                // if overlaps with another room, have to pick another location
                if (intersects(&rooms[i], &rooms[j])) {
                    failed = 1;
                    break;
                }
            }
            if (!failed) {
                initRoom(&rooms[i], map);
                if (i > 0)
                    drawCorridors(map, &rooms[i - 1], &rooms[i]);
                //rooms[i] = nr;
            }
        } while (failed);
    }
    // Player is initially placed in the center of first room
    game->position = rooms[0].center;
    free(rooms);  // not needed anymore
}

/* Generate game map by first filling everything as wall, then using
 * placeRooms above, to create rooms and corridors
 */
void generateMap(Game *game) {
    Map *map = &game->map;
    Options *opt = &game->opts;

    map->tile = malloc(sizeof (Tile *) * opt->mapHeight);
    for (unsigned int i = 0; i < opt->mapHeight; i++) {
        map->tile[i] = malloc(sizeof (Tile) * opt->mapWidth);
        for (unsigned int j = 0; j < opt->mapWidth; j++) {
            map->tile[i][j] = TILE_WALL;
        }
    }
    placeRooms(game);
}

/* Free all dynamically allocated memory
 */
void freeAll(Game *game) {
    if (game->map.tile) {
        for (unsigned int i = 0; i < game->opts.mapHeight; i++) {
            free(game->map.tile[i]);
        }
        free(game->map.tile);
    }
    if (game->monsters)
        free(game->monsters);
}

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
    if(!isBlocked(game, x,y) || (game->position.x == x && game->position.y == y)){
        monst->pos.x = x;
        return;
    }
    x = monst->pos.x;
    if(game->position.y > monst->pos.y)  {y++;} else if((game->position.y < monst->pos.y)) {y--;}
    if(!isBlocked(game, x,y) || (game->position.x == x && game->position.y == y)){
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
    if(game->position.x > monst->pos.x)  {x--;} else if((game->position.x < monst->pos.x)) {x++;}    
    if(!isBlocked(game, x,y) || (game->position.x == x && game->position.y == y)){
        monst->pos.x = x;
        return;
    }
    x = monst->pos.x;
    if(game->position.y > monst->pos.y)  {y--;} else if((game->position.y < monst->pos.y)) {y++;}
    if(!isBlocked(game, x,y) || (game->position.x == x && game->position.y == y)){
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
        } 
    }
    game->numMonsters = i;
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

/* Determine what character to show on the given map position.
 * 
 * Parameters:
 * game: the game state
 * x,y: map coordinates
 * 
 * Returns: character to be displayed
 */
char locationChar(const Game *game, int x, int y)
{
	const Map *map = &game->map;
	char c = '?';
	switch(map->tile[y][x]) {
	case TILE_WALL:
		c = '#';
		break;
	case TILE_OPEN:
		c = '.';
		break;
	case TILE_ROOM:
		c = '.';
		break;
	}

        for (unsigned int i = 0; i < game->numMonsters; i++) {
            if (game->monsters[i].pos.x == x && game->monsters[i].pos.y == y) {
                c = game->monsters[i].sign;
                break;
            }
        }
	
	if (game->position.x == x && game->position.y == y) {
		c = '*';
	}
	return c;
}


/* Show full map, without adhering to the visibility rules
 */
void printMap(const Game *game)
{
    const Options *opt = &game->opts;
	for (int i = 0; i < (int) opt->mapHeight; i++) {
		for (int j = 0; j < (int) opt->mapWidth; j++) {
			char c = locationChar(game, j, i);
			printf("%c", c);
		}
		printf("\n");
	}
}

// determine whether x1,y1 is within line of sight from x0,y0
// (assume |x1-x0| > |y1-y0|)
int isVisibleX(const Map *map,int x0, int x1, int y0, int y1)
{
	int x = x0;
	int y = y0;
	int dx = (x1 >= x0) ? 1 : -1;
	float cy = y0;
	int vis = 1;
	while (x != x1) {
		float dy = ((float)y1 - y) / abs(x1 - x);
		if (!vis) return 0;
		if (map->tile[y][x] == TILE_WALL) {
			vis = 0;
		}
		if (dy < 0)
			cy += ceil(dy);
		else
			cy += floor(dy);
		y = cy;
		x += dx;
	}
	return vis;
}

// determine whether x1,y1 is within line of sight from x0,y0
// (assume |y1-y0| > |x1-x0|)
int isVisibleY(const Map *map,int x0, int x1, int y0, int y1)
{
	int x = x0;
	int y = y0;
	int dy = (y1 >= y0) ? 1 : -1;
	float cx = x0;
	int vis = 1;
	while (y != y1) {
		float dx = ((float)x1 - x) / abs(y1 - y);
		if (!vis) return 0;
		if (map->tile[y][x] == TILE_WALL) {
			vis = 0;
		}
		if (dx < 0)
			cx += ceil(dx);
		else
			cx += floor(dx);
		x = cx;
		y += dy;
	}
	return vis;
}

// Crude algorithm for determining whether x1,y1 is within line of sight from x0,y0
int isVisible(const Map *map, int x0, int x1, int y0, int y1)
{
	if (x0 == x1 && y0 == y1)
		return 1;

	if (abs(x1-x0) > abs(y1-y0)) {
		return(isVisibleX(map, x0, x1, y0, y1));
	} else {
		return(isVisibleY(map, x0, x1, y0, y1));
	}
}


/* Show map around character, adhering to the visibility rules
 */
void printMe(const Game *game)
{      
    const Options *opt = &game->opts;
	for (int i = game->position.y - (int)opt->visibility; 
	     i <= game->position.y + (int)opt->visibility; i++) {
		for (int j = game->position.x - (int)opt->visibility;
		     j <= game->position.x + (int)opt->visibility; j++) {
			char c = ' ';
			if (i >= 0 && i < (int) opt->mapHeight &&
			    j >= 0 && j < (int) opt->mapWidth) {
				if (isVisible(&game->map, game->position.x, j,
					      game->position.y, i))
					c = locationChar(game, j, i);
			}
			printf("%c", c);
		}
		printf("\n");
	}
}

/* Exercise (a)
 *
 * Returns 1, if player character is not allowed to move to
 * given position (x,y). Returns 0, if moving is allowed
 */
int isBlocked(const Game *game, int x, int y)
{
	if(game->opts.mapHeight < (unsigned)y || game->opts.mapWidth < (unsigned)x) return 1;
	if(game->map.tile[y][x] == TILE_WALL) return 1;
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        if (game->monsters[i].pos.x == x && game->monsters[i].pos.y == y) {
            return 1;
        }
    }
	return 0;
}

/* Attack the given monster
 */

void attackMonster(Creature *monst)
{
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        monst->hp = monst->hp - dam;
        if (monst->hp <= 0) {
            printf("Monster died!");
            monst->pos.x = -1;
            monst->pos.y = -1;
        } else {
            printf("Monster HP: %d (%d) ", (int)monst->hp, monst->maxhp);
        }

    } else {
        printf("Miss!");
    }
}

/* Check if there is monster in given location.
 * If yes, attack it.
 */
int checkMonster(Game *game, int x, int y)
{
    Creature *monst = game->monsters;
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        if (monst[i].pos.x == x && monst[i].pos.y == y) {
            printf("Attacking monster! ");
            attackMonster(&monst[i]);
            printf("\n");
            return 1;
        }
    }
    return 0;
}

/* Move to given location, if possible
 */
void moveIfCan(Game *game, int x, int y)
{
    if (checkMonster(game, x, y)) {
        return;
    }
    if (!isBlocked(game, x, y)) {
        game->position.x = x;
        game->position.y = y;
    } else {
        printf("Blocked\n");
    }
}

/* Show map and player hit points
 * Either full map is shown, or just the visible portion around player,
 * depending on opts.showAll value
 */
void showMap(const Game *game)
{
    if (game->opts.showAll) {
        printMap(game);
    } else {
        printMe(game);
    }
    printf("HP: %d(%d)\n", (int)game->hp, game->maxhp);
}

/* Parse command given by user
 * 
 * Parameters:
 * game: game state
 * buf: one line read from user
 * 
 * Returns: 1, if game continues; 0 if game ends
 */
int doCommand(Game *game, char *buf)
{
    int newx = game->position.x;
    int newy = game->position.y;
    switch(tolower((int)buf[0])) {
	case 'n':
		newy--;
		break;
	case 's':
		newy++;
		break;
	case 'w':
		newx--;
		break;
	case 'e':
		newx++;
		break;
        case 'q':
                return 0; // game over
                
	default:
		printf("what???\n");
		break;
	}
        moveIfCan(game, newx, newy);
        monsterAction(game);
        checkIntent(game);
        if (game->hp <= 0)
            return 0;  // game over!
        if (game->hp < game->maxhp)
            game->hp = game->hp + 0.1;  // heals a bit every turn
        
        return 1;
}

/* Sets global options for the game (map size, num. of monsters, etc.)
 * 
 * Parameters:
 * game: the game state
 * argc: number of command line arguments
 * argv: array of command line arguments
 */
void setOptions(Game *game, int argc, char **argv)
{
	(void) argc;
	(void) argv;
    Options *opt = &game->opts;
    opt->numRooms = 12;
    opt->minRoomSize = 3;
    opt->maxRoomSize = 8;
    opt->mapWidth = 70;
    opt->mapHeight = 40;
    opt->numMonsters = 10;
    opt->visibility = 5;
    opt->showAll = 0;
}


int main(int argc, char **argv)
{
	Game game;
        memset(&game, 0, sizeof(game));
	srand((unsigned)time(NULL));
	//srand(1);
        setOptions(&game, argc, argv);
        if (game.map.tile == NULL) {
            // NULL, unless setOptions loaded previous game
	    generateMap(&game);
            createMonsters(&game);
            game.maxhp = 12;
            game.hp = game.maxhp;
        }
        int gameOn = 1;
        while(gameOn) {
		char buffer[80];
		showMap(&game);
		printf("command >");
		fgets(buffer, sizeof(buffer), stdin);
		gameOn = doCommand(&game, buffer);
	}
	freeAll(&game);
}
