#pragma once

#include "raylib.h"
#include "map/map.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct CirclePoint {
    Vector2 position;
    float angle;
} CirclePoint;

Vector2 GetPointInMap(Map* map);
CirclePoint* GetPointsOnCircle(int count, float arcLength, float centerAngle, Vector2 position, float radius);