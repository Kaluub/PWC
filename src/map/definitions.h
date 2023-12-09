#pragma once

#include "raylib.h"
#include "../entities/definitions.h"

#define MAX_WALL_COUNT 64
#define MAX_TILE_COUNT 32
#define MAX_ENEMY_COUNT 256

typedef enum TileType {
    SLOWING, // Decreases speed by 50%.
    ACCELERATING, // Increases speed by 50%.
    HORIZONTAL_NULLIFICATION, // Prevents movement in the x direction.
    VERTICAL_NULLIFICATION, // Prevents movement in the y direction.
    REVERSING, // Reverses velocity. Best used as a full area tile.
} TileType;

typedef struct Wall {
    Rectangle area;
    Color color;
    TargetType targetType;
} Wall;

typedef struct Tile {
    Rectangle area;
    Color color;
    TileType tileType;
} Tile;

typedef struct Map {
    Rectangle area;
    Wall walls[MAX_WALL_COUNT];
    Tile tiles[MAX_TILE_COUNT];
    Enemy enemies[MAX_ENEMY_COUNT];
    int wallCount;
    int tileCount;
    int enemyCount;
    Color color;
} Map;