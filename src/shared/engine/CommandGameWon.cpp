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

Json::Value CommandGameWon::Serialize () {
  Json::Value val;
  val["typeCmd"] = "GameWon";
  return val;
}
 CommandGameWon* CommandGameWon::Deserialize (Json::Value in){
  return this;
}
