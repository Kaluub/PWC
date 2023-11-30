#include "minimize.h"
#include "../entities/player.h"
#include "../utils.h"
#include "../entities/minimize_projectile.h"
#include <math.h>
#include <malloc.h>

void ActivateMinimize(Player *player, Minimize *minimize) {
    if (minimize->data.cooldown > 0) {
        return;
    }

    int numberOfProjectiles = minimize->data.level + 1;
    MinimizeProjectile* projectiles = (MinimizeProjectile*) calloc(numberOfProjectiles + minimize->projectileCount, sizeof(MinimizeProjectile));
    if (projectiles == NULL) {
        // Could not create space for new projectiles.
        return;
    }
    if (minimize->projectiles != NULL) {
        // Copy old projectiles over.
        for (int i = 0; i < minimize->projectileCount; i += 1) {
            projectiles[i] = minimize->projectiles[i];
        }
        free(minimize->projectiles);
    }
    minimize->projectiles = projectiles;

    minimize->data.totalCooldown = 5;
    minimize->data.cooldown = 5;

    float projectileRadius = 10;
    int projectileSpeed = 280;

    CirclePoint* points = GetPointsOnCircle(
        numberOfProjectiles,
        DEG2RAD*(15+(minimize->data.level-1)*8),
        player->inputAngle,
        player->position,
        projectileRadius
    );
    if (points == NULL) {
        return;
    }

    for (int i = 0; i < numberOfProjectiles; i += 1) {
        // Spawn new projectiles.
        CirclePoint point = points[i];
        MinimizeProjectile projectile = (MinimizeProjectile) {
            point.position,
            (Vector2) {cosf(point.angle), sinf(point.angle)},
            projectileRadius,
            projectileSpeed,
            2.5
        };
        projectiles[minimize->projectileCount] = projectile;
        minimize->projectileCount += 1;
    }

    // Free points memory
    free(points);
    points = NULL;
}

void UpdateMinimize(Player *player, Map *map, Minimize *minimize) {
    if (minimize->data.cooldown > 0) {
        minimize->data.cooldown -= GetFrameTime();
    }

    // If projectiles exist, update them
    if (minimize->projectiles != NULL) {
        for (int i = 0; i < minimize->projectileCount; i += 1) {
            MinimizeProjectile *projectile = &minimize->projectiles[i];
            UpdateMinimizeProjectile(projectile, map);
            if (projectile->duration <= 0) {
                // Remove current projectile.
                minimize->projectileCount -= 1;
                minimize->projectiles[i] = minimize->projectiles[minimize->projectileCount];
                // Update target projectile.
                if (i < minimize->projectileCount) {
                    i -= 1;
                }
            }
        }
    } else if (minimize->projectileCount != 0) {
        // Should never happen!
        TraceLog(LOG_ERROR, "Minimize projectile count is not accurate! (UpdateMinimize)");
        minimize->projectileCount = 0;
    }
}