#include "utils.h"

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

Vector2 GetPointInMap(Map* map) {
    return (Vector2) {GetRandomValue(map->area.x, map->area.x + map->area.width), GetRandomValue(map->area.y, map->area.y + map->area.height)};
}