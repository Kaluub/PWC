#include "ability.h"

void ActivateAbility(Player *player, Map *map, Ability *ability, AbilityType abilityType) {
    // Select the correct ability activation function based on the slot's ability type.
    switch (abilityType) {
        case NONE:
            return;
        case NIGHT:
            ActivateNight(player, &ability->night);
            return;
        case DEPART:
            ActivateDepart(player, &ability->depart);
            return;
        case HARDEN:
            ActivateHarden(player, &ability->harden);
            return;
        case MINIMIZE:
            ActivateMinimize(player, &ability->minimize);
            return;
    }
}

void UpdateAbility(Player *player, Map *map, Ability *ability, AbilityType abilityType) {
    // Select the correct ability update function based on the slot's ability type.
    switch (abilityType) {
        case NONE:
            return;
        case NIGHT:
            UpdateNight(player, &ability->night);
            return;
        case DEPART:
            UpdateDepart(player, &ability->depart);
            return;
        case HARDEN:
            UpdateHarden(player, &ability->harden);
            return;
        case MINIMIZE:
            UpdateMinimize(player, map, &ability->minimize);
            return;
    }
}

Texture2D GetAbilityIcon(GameState *gameState, AbilityType abilityType) {
    switch (abilityType) {
        case NIGHT:
            return gameState->textures.night;
        case DEPART:
            return gameState->textures.depart;
        case HARDEN:
            return gameState->textures.harden;
        case MINIMIZE:
            return gameState->textures.minimize;
        case NONE:
        default:
            return gameState->textures.defaultAbility;
    }
}