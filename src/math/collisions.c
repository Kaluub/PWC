#include <math.h>
#include <string.h>

#include "collisions.h"
#include "raymath.h"

Vector2 ClosestPointOnRect(Rectangle rect, Vector2 point) {
    Vector2 closestPoint;
    closestPoint.x = fmaxf(rect.x, fminf(point.x, rect.x + rect.width));
    closestPoint.y = fmaxf(rect.y, fminf(point.y, rect.y + rect.height));
    return closestPoint;
}

int IsPointInRect(Rectangle rect, Vector2 point) {
    return (point.x > rect.x && point.x < rect.x + rect.width &&
            point.y > rect.y && point.y < rect.y + rect.height);
}

int IsCircleInRect(Vector2 position, float radius, Rectangle rect) {
    Vector2 closestPoint = ClosestPointOnRect(rect, position);
    float distanceSquared = Vector2DistanceSqr(position, closestPoint);
    return distanceSquared < (radius * radius);
}

Vector2 GetMTVCircleRects(CircleCollider circle, Rectangle* rects, int rectCount) {
    Vector2 result = {0, 0};

    for (int i = 0; i < rectCount; i += 1) {
        Rectangle rect = rects[i];

        Vector2 closestPoint = ClosestPointOnRect(rect, circle.position);
        float distance = Vector2Distance(circle.position, closestPoint);

        if (distance < circle.radius) {
            float leftDist = circle.position.x - rect.x + circle.radius;
            float rightDist = (rect.x + rect.width) - circle.position.x + circle.radius;
            float topDist = circle.position.y - rect.y + circle.radius;
            float bottomDist = (rect.y + rect.height) - circle.position.y + circle.radius;

            float minDist = fminf(fminf(leftDist, rightDist), fminf(topDist, bottomDist));
            Vector2 direction;

            if (minDist == leftDist) {
                direction = (Vector2) {-1, 0};
            } else if (minDist == rightDist) {
                direction = (Vector2) {1, 0};
            } else if (minDist == topDist) {
                direction = (Vector2) {0, -1};
            } else {
                direction = (Vector2) {0, 1};
            }

            Vector2 mtv = {direction.x * minDist, direction.y * minDist};
            result.x += mtv.x;
            result.y += mtv.y;
        }
    }

    return result;
}