#include "CommandEndFight.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandEndFight::CommandEndFight (bool isFightWon): isFightWon(isFightWon){}

CommandEndFight::CommandEndFight (){}

void CommandEndFight::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"End fight"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

  if (!isFightWon){
    gameState->GetRules()->SetIsGameLost(true);
    gameState->GetRules()->SetIsGameOver(true);
  }

  room->SetIsGameLost(!isFightWon);
  room->SetIsFightWon(isFightWon);
}

void CommandEndFight::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo End fight"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();

  gameState->GetRules()->SetIsGameLost(false);
  gameState->GetRules()->SetIsGameOver(false);

  room->SetIsGameLost(false);
  room->SetIsFightWon(false);
}

json_map CommandEndFight::Serialize () {
  json_map val;
  return val;
}
 CommandEndFight* CommandEndFight::Deserialize (json_map in){
  return this;
}
