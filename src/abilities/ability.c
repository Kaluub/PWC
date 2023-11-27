#include "ability.h"

void ActivateAbility(Player *player, Ability *ability, AbilityType abilityType) {
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
    }
}

void UpdateAbility(Player *player, Ability *ability, AbilityType abilityType) {
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
    }
}