#include "minimize.h"
#include "../entities/player.h"
#include "../utils.h"
#include "../entities/minimize_projectile.h"
#include <math.h>
#include <malloc.h>

void ActivateMinimize(Player* player, Minimize* minimize) {
    if (minimize->data.cooldown > 0) {
        return;
    }

    int numberOfProjectiles = minimize->data.level + 1;
    minimize->projectiles = realloc(minimize->projectiles, sizeof(MinimizeProjectile) * (minimize->projectileCount + numberOfProjectiles));
    if (minimize->projectiles == NULL) {
        // Could not create space for new projectiles.
        TraceLog(LOG_WARNING, "Could not make space for MinimizeProjectiles (ActivateMinimize)");
        return;
    }

    minimize->data.totalCooldown = 1;
    minimize->data.cooldown = 1;

    float projectileRadius = 10;
    int projectileSpeed = 280;

    CirclePoint* points = GetPointsOnCircle(
        numberOfProjectiles,
        DEG2RAD*(15+(minimize->data.level-1)*8),
        player->inputAngle,
        player->position,
        player->radius
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
        minimize->projectiles[minimize->projectileCount] = projectile;
        minimize->projectileCount += 1;
    }

    // Free points memory
    free(points);
    points = NULL;
}

void UpdateMinimize(Player* player, Map* map, Minimize* minimize) {
    if (minimize->data.cooldown > 0) {
        minimize->data.cooldown -= GetFrameTime();
    }

    // If projectiles exist, update them
    if (minimize->projectiles != NULL) {
        for (int i = 0; i < minimize->projectileCount; i += 1) {
            MinimizeProjectile* projectile = &minimize->projectiles[i];
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
    }
    if (minimize->projectileCount == 0) {
        free(minimize->projectiles);
        minimize->projectiles = NULL;
    }
}

void DrawMinimizeProjectiles(Minimize* minimize) {
    for (int i = 0; i < minimize->projectileCount; i += 1) {
        MinimizeProjectile projectile = minimize->projectiles[i];
        DrawMinimizeProjectile(projectile);
    }
}