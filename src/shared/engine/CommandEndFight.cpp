#include "CommandEndFight.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandEndFight::CommandEndFight (bool isFightWon): isFightWon(isFightWon){}

CommandEndFight::CommandEndFight (){}

void CommandEndFight::Execute (std::shared_ptr<state::GameState>& gameState){


  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  bool res = false;
  for(auto& enemy : room->GetEnemies()){
    if enemy->GetIsEntityAlive() res = true;
  }
  if(!res){
    cout<<"End fight"<<endl;
    room->SetEntityTurn(0);
    if (!isFightWon){
      gameState->GetRules()->SetIsGameLost(true);
      gameState->GetRules()->SetIsGameOver(true);
    } else{
      for(state::Player* player : gameState->GetPlayers()){
        if(!player->GetIsEntityAlive()){
          player->SetLife(1);
          player->SetIsEntityAlive(true);
        }
      }
    }

    room->SetIsGameLost(!isFightWon);
    room->SetIsFightWon(isFightWon);
  }
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

Json::Value CommandEndFight::Serialize () {
  Json::Value val;
  val["typeCmd"] = "EndFight";
  val["isFightWon"] = isFightWon;
  return val;
}
 CommandEndFight* CommandEndFight::Deserialize (Json::Value in){
   isFightWon = in["isFightWon"].asBool();
  return this;
}
