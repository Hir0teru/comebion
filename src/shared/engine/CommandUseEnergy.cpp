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
void CommandUseEnergy::Execute(std::shared_ptr<state::GameState> gamestate){
  if(entityID >=0 && entityID < 2){
    Player * player = gamestate -> GetPlayers()[entityID];
    if( player -> GetEnergy() < energyAmount){
      player -> SetEnergy(0);
    } else player -> SetEnergy(energyAmount);
  }
}

void CommandUseEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  if(entityID >=0 && entityID < 2){
    Player * player = gamestate -> GetPlayers()[entityID];
    player -> SetEnergy(player -> GetEnergy() + energyAmount);
  }
}
Json::Value CommandUseEnergy::Serialize () const {}
static Command* Engine::Deserialize (const Json::Value& track) {}
