#include "CommandExitRoom.h"
#include "CommandChangeRoom.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandExitRoom::CommandExitRoom (){}

void CommandExitRoom::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Exit current room"<<endl;
  gameState->SetIsInsideRoom(false);
  CommandChangeRoom command;
  command.Execute(gameState);
}

void CommandExitRoom::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Exit current room"<<endl;
  gameState->SetIsInsideRoom(true);
  CommandChangeRoom command;
  command.Undo(gameState);
}

json_map CommandExitRoom::Serialize () {
  json_map val;
  return val;
}
 CommandExitRoom* CommandExitRoom::Deserialize (json_map in){
  return this;
}
