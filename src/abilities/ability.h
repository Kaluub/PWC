#pragma once

#include "definitions.h"
#include "../entities/definitions.h"
#include "../map/definitions.h"
#include "../states.h"

#include "night.h"
#include "depart.h"
#include "harden.h"
#include "minimize.h"

void ActivateAbility(Player *player, Map *map, Ability *ability, AbilityType abilityType);
void UpdateAbility(Player *player, Map *map, Ability *ability, AbilityType abilityType);
Texture2D GetAbilityIcon(GameState *gameState, AbilityType abilityType);