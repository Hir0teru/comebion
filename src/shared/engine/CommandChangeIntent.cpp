#include "CommandChangeIntent.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandChangeIntent::CommandChangeIntent (int entityID, int element): entityID(entityID), element(element){}

CommandChangeIntent::CommandChangeIntent (){}

void CommandChangeIntent::Execute (std::shared_ptr<state::GameState>& gameState){
  //TODO: How to do it ??
}

void CommandChangeIntent::Undo (std::shared_ptr<state::GameState>& gameState){
  //TODO: How to undo it ?
}
