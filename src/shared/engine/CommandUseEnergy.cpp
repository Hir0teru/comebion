#include "CommandUseEnergy.h"


using namespace engine;


CommandUseEnergy::CommandUseEnergy(){
  entityID = 0;
  energyAmount = 0;
}

CommandUseEnergy::CommandUseEnergy(int energyAmount, int playerId){
  this -> entityID = playerId;
  this -> energyAmount = energyAmount;
}
void CommandUseEnergy::Execute(std::shared_ptr<state::GameState>& gameState){
  if(entityID >=0 && entityID < 2){
    if( gameState -> GetPlayers()[entityID] -> GetEnergy() < energyAmount){
       gameState -> GetPlayers()[entityID]-> SetEnergy(0);
    } else  gameState -> GetPlayers()[entityID] -> SetEnergy(energyAmount);
  }
}

void CommandUseEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  if(entityID >=0 && entityID < 2){
     gameState -> GetPlayers()[entityID] -> SetEnergy(gameState -> GetPlayers()[entityID] -> GetEnergy() + energyAmount);
  }
}
