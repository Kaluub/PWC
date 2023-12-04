#include "depart.h"

void ActivateDepart(Player *player, Depart *depart) {
    if (depart->data.cooldown > 0) {
        return;
    }

    depart->data.cooldown = 8;
    depart->data.totalCooldown = 8;
    depart->duration = 3;
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