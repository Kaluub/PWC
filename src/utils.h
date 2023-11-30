#pragma once

#include "raylib.h"
#include "map/map.h"

typedef struct CirclePoint {
    Vector2 position;
    float angle;
} CirclePoint;

int min(int a, int b);
int max(int a, int b);
Vector2 GetPointInMap(Map* map);
CirclePoint* GetPointsOnCircle(int count, float arcLength, float centerAngle, Vector2 position, float radius);