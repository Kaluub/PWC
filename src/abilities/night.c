#include "night.h"

void ActivateNight(Player* player, Night* night) {
    if (night->data.cooldown > 0) {
        return;
    }

    night->data.cooldown = 5.5;
    night->data.totalCooldown = 5.5;
    night->duration = 5;
    night->nightSpeed = 100;
}

void UpdateNight(Player* player, Night* night) {
    if (night->data.cooldown > 0) {
        night->data.cooldown -= GetFrameTime();
    }
    
    if (night->duration <= 0) {
        return;
    }

    night->duration -= GetFrameTime();
    player->speedBoost += night->nightSpeed;
    player->alpha *= 0.7;
}