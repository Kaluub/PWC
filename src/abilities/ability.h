#pragma once

#include "definitions.h"
#include "../entities/definitions.h"

#include "night.h"
#include "depart.h"
#include "harden.h"

void ActivateAbility(Player *player, Ability *ability, AbilityType abilityType);
void UpdateAbility(Player *player, Ability *ability, AbilityType abilityType);