#include "depart.h"
#include "../utils.h"

void ActivateDepart(Player *player, Depart *depart) {
    if (depart->data.cooldown > 0) {
        return;
    }

    depart->data.totalCooldown = max(8 - 0.5 * depart->data.level, 0);
    depart->data.cooldown = depart->data.totalCooldown;
    depart->duration = 2 + 0.3 * depart->data.level;
}

void UpdateDepart(Player *player, Depart *depart) {
    if (depart->data.cooldown > 0) {
        depart->data.cooldown -= GetFrameTime();
    }
    
    if (depart->duration <= 0) {
        player->isDeparted = 0;
        return;
    }

    depart->duration -= GetFrameTime();
    player->speedMultiplier *= 0.5;
    player->alpha *= 0;
    player->isDeparted = 1;
}