#pragma once

#include "raylib.h"

typedef struct CircleCollider {
    Vector2 position;
    float radius;
} CircleCollider;

Vector2 ClosestPointOnRect(Rectangle rect, Vector2 point);
int IsPointInRect(Rectangle rect, Vector2 point);
int IsCircleInRect(Vector2 position, float radius, Rectangle rect);
Vector2 GetMTVCircleRects(CircleCollider circle, Rectangle* rects, int rectCount);