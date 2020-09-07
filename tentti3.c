#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// MapTile structure holds the center location for the map tile,
// and its id, size and zoom
typedef struct mapTile MapTile;

struct mapTile {
    double centerLocation[2];
    char id[15];
    double size;
    int zoom;
    MapTile* next;
};

// Map structure holds the map tile data for the map location
// as a MapTile structure array, as well as the amount of map tiles
// in the array and the name of the location for the map.
typedef struct map {
    MapTile* mapTiles;
    char* locationName;
} Map;

// Function createMapTile creates a linked list member with the given data.
MapTile* createMapTile(char* tileId, int zoom, double size,
                       double centerLocation[2]) {

    // Allocate memory for map tile
    MapTile* tile = malloc(sizeof(MapTile));

    tile->size = size; //strcpy(tile->size, size);
    tile->zoom = zoom;
    // Save the name
    //tile->id = malloc(strlen(tileId) + 1);
    strcpy(tile->id, tileId);

    // Save the center coordinate
    tile->centerLocation[0] = centerLocation[0];
    tile->centerLocation[1] = centerLocation[1];

    // Set the next pointer
    tile->next = NULL;

    return tile;
}

// Function createMapTiles takes five parameters:
// - tileIds, an array of tile ids (strings)
// - zoom, the zoom level of map tiles
// - size, the width and height of a map tile
// - centerLocations, and array of pair of doubles
//   (latitude-longitude pairs)
// - tileAmount, and integer that tells how many tiles
//   there are in the arrays
// The function returns a MapTile structure linked list created
// from the data given as parameters
MapTile* createMapTiles(char** tileIds, int zoom, double size,
                        double centerLocations[][2], int tileAmount) {

    MapTile* tile = createMapTile(tileIds[0], zoom, size,
                                  centerLocations[0]);
    MapTile* start = tile; //*

    // Go through all the given data and store it in the array
    for(int i = 1; i < tileAmount; i++) {
        tile->next = createMapTile(tileIds[i], zoom, size,
                                   centerLocations[i]);
        tile = tile->next;
    }

    return start;
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
    Map* map = malloc(sizeof(Map)); // here

    // Store the location name
    map->locationName = malloc(strlen(locationName) + 1);
    strcpy(map->locationName, locationName);

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
    printf("%s has the following map tiles:\n", map->locationName);

    // Loop through the map tiles and print their info
    for(MapTile *current = map->mapTiles; current; current = current->next) { //*
        printf("Map tile id %s (size %.2f, zoom %d) is at (%f, %f).\n",
                    current->id, current->size, current->zoom,
                    current->centerLocation[0], current->centerLocation[1]);
    }
}

// Function freeMemory frees all the dynamic memory
// allocated for the Map structure
void freeMemory(Map* map) {
    for(MapTile* current = map->mapTiles; current; ) {
        MapTile* del = current;
        current = current->next;
        free(del);
        del = NULL;
    }

    free(map->locationName);
    free(map);
}

int main() {
    // Original data for map tiles:
    // Ids
    char* ids[] = { "17-74574-37927",
                    "17-74574-37928",
                    "17-74574-37929",
                    "17-74573-37927",
                    "17-74573-37928",
                    "17-74573-37929" };

    // Size is always the same at the same zoom level
    double size = 152.0819;
    int zoom = 17;

    // Tile center location, a latitude-longitude pair
    double centerLocations[][2] = { { 60.1859156214031, 24.8249816894531 },
                                  { 60.1845500274125, 24.8249816894531 },
                                  { 60.1831843766236, 24.8249816894531 },
                                  { 60.1859156214031, 24.8222351074219 },
                                  { 60.1845500274125, 24.8222351074219 },
                                  { 60.1831843766236, 24.8222351074219 } };

    // Create a map structure based on the data
    Map* map = createMap("Otaniemi", ids, zoom, size, centerLocations, 6);

    // Print map tiles information
    printTileInfo(map);

    // Free the reserved memory
    freeMemory(map);

    return 0;
}