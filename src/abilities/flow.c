#include "flow.h"
#include "../entities/player.h"

void ActivateFlow(Player* player, Flow* flow) {
    player->hasFlow = !player->hasFlow;
    player->isHard = 0;
}

void UpdateFlow(Player* player, Flow* flow) {
    if (player->hasFlow) {
        player->speedBoost += 30 + 30 * flow->data.level;
        AddColorEffect(player, (Color) {255, 80, 10, 255});
    }
}