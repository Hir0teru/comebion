#include "CommandAddEnergy.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAddEnergy::CommandAddEnergy (int entityID, int energyAmount): entityID(entityID), energyAmount(energyAmount){}

CommandAddEnergy::CommandAddEnergy (){}

void CommandAddEnergy::Execute (std::shared_ptr<state::GameState>& gameState){
  if (entityID >= 0 && entityID < 2 ){
    cout<<"Add "<<energyAmount<< " energy to entity "<<entityID<<endl;
    gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() + energyAmount);
  }
}

void CommandAddEnergy::Undo (std::shared_ptr<state::GameState>& gameState){
  if (entityID > 0 && entityID < 2 ){
    cout<<"Undo Adding "<<energyAmount<< " energy to entity "<<entityID<<"..."<<endl;
    gameState->GetPlayers()[entityID]->SetEnergy(gameState->GetPlayers()[entityID]->GetEnergy() - energyAmount);
  }
}
json_map CommandAddEnergy::Serialize () {
  json_map val;
  val["typeCmd"] = "AddEnergy";
  val["entityID"] = entityID;
  val["energyAmount"] = energyAmount;
  return val;
}
 CommandAddEnergy* CommandAddEnergy::Deserialize (json_map in){
   entityID = in["entityID"].as<json_int>();
   energyAmount = in["energyAmount"].as<json_int>();
  return this;
}
