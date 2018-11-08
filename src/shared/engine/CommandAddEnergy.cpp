#include "CommandAddEnergy.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandAddEnergy::CommandAddEnergy (int entityID, int energyAmount): entityID(entityID), energyAmount(energyAmount){}

CommandAddEnergy::CommandAddEnergy (){}

void CommandAddEnergy::Execute (std::shared_ptr<state::GameState>& gameState){
  gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() + energyAmount);
}

void CommandAddEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() - energyAmount);
}
