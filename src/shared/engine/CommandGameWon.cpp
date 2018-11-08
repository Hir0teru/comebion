#include "CommandGameWon.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandGameWon::CommandGameWon (){}

void CommandGameWon::Execute (std::shared_ptr<state::GameState>& gameState){
  gameState->GetRules()->SetIsGameOver(true);
}

void CommandGameWon::Undo (std::shared_ptr<state::GameState>& gameState){
  gameState->GetRules()->SetIsGameOver(false);
}
