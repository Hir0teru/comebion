#include "CommandChangeFloor.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandChangeFloor::CommandChangeFloor (){}

void CommandChangeFloor::Execute (std::shared_ptr<state::GameState>& gameState){
  gameState->GetMap()->SetCurrentFloor(gameState->GetMap()->GetCurrentFloor() + 1);
}

void CommandChangeFloor::Undo (std::shared_ptr<state::GameState>& gameState){
  gameState->GetMap()->SetCurrentFloor(gameState->GetMap()->GetCurrentFloor() - 1);
}
