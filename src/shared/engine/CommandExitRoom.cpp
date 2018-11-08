#include "CommandExitRoom.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandExitRoom::CommandExitRoom (){}

void CommandExitRoom::Execute (std::shared_ptr<state::GameState>& gameState){
  gameState->SetIsInsideRoom(false);
}

void CommandExitRoom::Undo (std::shared_ptr<state::GameState>& gameState){
  gameState->SetIsInsideRoom(true);
}
