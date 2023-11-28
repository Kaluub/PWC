#pragma once

#include "definitions.h"
#include "../entities/definitions.h"
#include "../states.h"

#include "night.h"
#include "depart.h"
#include "harden.h"

void ActivateAbility(Player *player, Ability *ability, AbilityType abilityType);
void UpdateAbility(Player *player, Ability *ability, AbilityType abilityType);
Texture2D GetAbilityIcon(GameState *gameState, AbilityType abilityType);