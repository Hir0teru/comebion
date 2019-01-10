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

Json::Value CommandExitRoom::Serialize () {
  Json::Value val;
  val["typeCmd"] = "ExitRoom";
  return val;
}
 CommandExitRoom* CommandExitRoom::Deserialize (Json::Value in){
  return this;
}
