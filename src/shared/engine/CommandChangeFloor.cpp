#include "CommandChangeFloor.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeFloor::CommandChangeFloor (){}

void CommandChangeFloor::Execute (std::shared_ptr<state::GameState>& gameState){
  if (gameState->GetMap()->GetCurrentFloor() < 3){
    cout<<"Change current floor to "<<(gameState->GetMap()->GetCurrentFloor() + 1)<<endl;
    gameState->GetMap()->SetCurrentFloor(gameState->GetMap()->GetCurrentFloor() + 1);
  }
}

void CommandChangeFloor::Undo (std::shared_ptr<state::GameState>& gameState){
  if (gameState->GetMap()->GetCurrentFloor() >= 0 ){
    cout<<"Undo Change current floor to "<<(gameState->GetMap()->GetCurrentFloor() - 1)<<endl;
    gameState->GetMap()->SetCurrentFloor(gameState->GetMap()->GetCurrentFloor() - 1);
  }
}
json_map CommandChangeFloor::Serialize () {
  json_map val;
  val["typeCmd"] = "ChangeFloor";
  return val;
}
 CommandChangeFloor* CommandChangeFloor::Deserialize (json_map in){
  return this;
}
