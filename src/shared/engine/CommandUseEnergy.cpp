#include "CommandUseEnergy.h"
#include <iostream>

using namespace engine;
using namespace std;

CommandUseEnergy::CommandUseEnergy(){
  entityID = 0;
  energyAmount = 0;
}

CommandUseEnergy::CommandUseEnergy(int energyAmount, int playerId){
  this -> entityID = playerId;
  this -> energyAmount = energyAmount;
}
void CommandUseEnergy::Execute(std::shared_ptr<state::GameState>& gameState){
  cout<<"Use "<<energyAmount<<" energy of player "<<entityID<<endl;
  if(entityID >=0 && entityID < 2){
    gameState -> GetPlayers()[entityID] -> SetEnergy(energyAmount);
  }
}

void CommandUseEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Use "<<energyAmount<<" energy of player "<<entityID<<endl;
  if(entityID >=0 && entityID < 2){
     gameState -> GetPlayers()[entityID] -> SetEnergy(gameState -> GetPlayers()[entityID] -> GetEnergy() + energyAmount);
  }
}
