#include "CommandGameWon.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandGameWon::CommandGameWon (){}

void CommandGameWon::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Game Won"<<endl;
  gameState->GetRules()->SetIsGameOver(true);
}

void CommandGameWon::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Game Won"<<endl;
  gameState->GetRules()->SetIsGameOver(false);
}
