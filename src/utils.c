#include "utils.h"
#include <math.h>
#include <malloc.h>

Vector2 GetPointInMap(Map* map) {
    return (Vector2) {GetRandomValue(map->area.x, map->area.x + map->area.width), GetRandomValue(map->area.y, map->area.y + map->area.height)};
}

CirclePoint* GetPointsOnCircle(int count, float arcLength, float centerAngle, Vector2 position, float radius) {
    CirclePoint *points = (CirclePoint*) calloc(count, sizeof(CirclePoint));
    if (points == NULL) {
        return NULL;
    }

    if (count == 1) {
        points[0] = (CirclePoint) {
            (Vector2) {
                position.x + radius * cosf(centerAngle),
                position.y + radius * sinf(centerAngle)
            },
            centerAngle
        };
        return points;
    }

    float startAngle = centerAngle - arcLength/2;
    float endAngle = centerAngle + arcLength/2;
    float angleIncrement = (endAngle - startAngle) / (count - 1);
    float currentAngle = startAngle;

    for (int i = 0; i < count; i += 1) {
        points[i] = (CirclePoint) {
            (Vector2) {
                position.x + radius * cosf(currentAngle),
                position.y + radius * sinf(currentAngle)
            },
            currentAngle
        };
        currentAngle += angleIncrement;
    }

    return points;
}