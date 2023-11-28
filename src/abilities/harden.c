#include "harden.h"
#include "../entities/player.h"

void ActivateHarden(Player *player, Harden *harden) {
    if (harden->data.cooldown > 0) {
        return;
    }

    harden->data.cooldown = 0.5;
    harden->data.totalCooldown = 0.5;
    player->isHard = !player->isHard;
}

void UpdateHarden(Player *player, Harden *harden) {
    if (harden->data.cooldown > 0) {
        harden->data.cooldown -= GetFrameTime();
    }

    if (player->isHard) {
        player->speedMultiplier *= 0;
        AddColorEffect(player, (Color) {200, 70, 0, 255});
    }
}