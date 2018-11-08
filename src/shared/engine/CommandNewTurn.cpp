#include "CommandNewTurn.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandNewTurn::CommandNewTurn (){}

void CommandNewTurn::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  room->SetTurn(room->GetTurn() + 1);
}

void CommandNewTurn::Undo (std::shared_ptr<state::GameState>& gameState){
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  room->SetTurn(room->GetTurn() - 1);
}
