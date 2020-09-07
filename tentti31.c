#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// MapTile structure holds the center location for the map tile,
// and its id, size and zoom
typedef struct mapTile {
    double centerLocation[2];
    char id[15];
    double size;
    int zoom;
} MapTile;

// Map structure holds the map tile data for the map location
// as a MapTile structure array, as well as the amount of map tiles
// in the array and the name of the location for the map.
typedef struct map {
    MapTile* mapTiles;
    int tileAmount;
    char* locationName;
} Map;

// Function createMapTiles takes five parameters:
// - tileIds, an array of tile ids (strings)
// - zoom, the zoom level of map tiles
// - size, the width and height of a map tile
// - centerLocations, and array of pair of doubles
//   (latitude-longitude pairs)
// - tileAmount, and integer that tells how many tiles
//   there are in the arrays
// The function returns a MapTile structure array created
// from the data given as parameters
MapTile* createMapTiles(char** tileIds, int zoom, double size,
                        double centerLocations[][2], int tileAmount) {

    // Allocate memory for map tiles, based on the given tileAmount
    MapTile* maptiles = malloc(sizeof(MapTile) * tileAmount);

    // Go through all the given data and store it in the array
    for(int i = 0; i < tileAmount; i++) {
        strcpy(maptiles[i].id, tileIds[i]);
        //maptiles[i].id = tileIds[i];
        maptiles[i].zoom = zoom;
        maptiles[i].size = size;

        // Copy the center location of the map tile
        maptiles[i].centerLocation[0] = centerLocations[i][0];
        maptiles[i].centerLocation[1] = centerLocations[i][1];
    }

    return maptiles;
}

// Function createMap takes six parameters:
// - locationName, a string that tells the map location name
// - tileIds (forwarded to the createMapTiles function, see it for details)
// - zoom (forwarded to the createMapTiles function, see it for details)
// - size (forwarded to the createMapTiles function, see it for details)
// - centerLocations (forwarded to the createMapTiles function)
// - tileAmount (forwarded to the createMapTiles function)
Map* createMap(char* locationName, char** tileIds, int zoom, double size,
               double centerLocations[][2], int tileAmount) {

    // Allocate memory for the Map structure
    Map* map = malloc(sizeof(Map));

    // Store the tile amount
    map->tileAmount = tileAmount;

    // Store the location name
    map->locationName = malloc(strlen(locationName) * sizeof(char) + 1);
    strcpy(map->locationName, locationName);
    //map->locationName = locationName;

    // Store the map tiles information
    map->mapTiles = createMapTiles(tileIds, zoom, size, centerLocations,
                                   tileAmount);

    return map;
}

// Function printTileInfo prints the Map structure information
// in the following format:
//
// <place name> has the following map tiles:
// Map tile id <id> (size <size>, zoom <zoom>) is at (latitude, longitude).
// ...
void printTileInfo(Map* map) {
    printf("%s has the following map tiles:\n", map->locationName); //*map->locationName);

    // Loop through the map tiles and print their info
    for(int i = 0; i < map->tileAmount; i++) {
        printf("Map tile id %s (size %.2f, zoom %d) is at (%f, %f).\n",
                map->mapTiles[i].id, map->mapTiles[i].size,
                map->mapTiles[i].zoom, map->mapTiles[i].centerLocation[0],
                map->mapTiles[i].centerLocation[1]);
    }
}

// Function freeMemory frees all the dynamic memory
// allocated for the Map structure
void freeMemory(Map* map) {
    free(map->locationName);
    free(map->mapTiles);
    free(map);
}