#include "CommandAddEnergy.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAddEnergy::CommandAddEnergy (int entityID, int energyAmount): entityID(entityID), energyAmount(energyAmount){}

CommandAddEnergy::CommandAddEnergy (){}

void CommandAddEnergy::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Add "<<energyAmount<< " energy to entity "<<entityID<<endl;
  gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() + energyAmount);
}

void CommandAddEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Adding "<<energyAmount<< " energy to entity "<<entityID<<"..."<<endl;
  gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() - energyAmount);
}
