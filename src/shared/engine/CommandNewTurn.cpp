#include "CommandNewTurn.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandNewTurn::CommandNewTurn (){}

void CommandNewTurn::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Next Turn"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  room->SetTurn(room->GetTurn() + 1);
}

void CommandNewTurn::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Next Turn"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  room->SetTurn(room->GetTurn() - 1);
}

Json::Value CommandNewTurn::Serialize () {
  Json::Value val;
  val["typeCmd"] = "NewTurn";
  return val;
}
 CommandNewTurn* CommandNewTurn::Deserialize (Json::Value in){
  return this;
}
