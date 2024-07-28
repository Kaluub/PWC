#include "harden.h"
#include "../entities/player.h"

void ActivateHarden(Player* player, Harden* harden) {
    if (harden->data.cooldown > 0) {
        return;
    }

    player->isHard = !player->isHard;
    player->hasFlow = 0;
    
    if (!player->isHard) {
        harden->data.totalCooldown = 1.5 - harden->data.level * 0.25;
        harden->data.cooldown = harden->data.totalCooldown;
    }
}

void UpdateHarden(Player* player, Harden* harden) {
    if (harden->data.cooldown > 0) {
        harden->data.cooldown -= GetFrameTime();
    }

    if (player->isHard) {
        player->speedMultiplier *= 0;
        AddColorEffect(player, (Color) {200, 70, 0, 255});
    }
}