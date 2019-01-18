#include "CommandEnterRoom.h"
#include "state/PlayerManager.h"
#include "CommandDraw.h"
#include "CommandShuffle.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandEnterRoom::CommandEnterRoom (){}

void CommandEnterRoom::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Enter current room"<<endl;
  gameState->SetIsInsideRoom(true);
  int floorNb = gameState->GetMap()->GetCurrentFloor();

  if((int)gameState->GetPlayers().size() == 2 && !gameState->GetPlayers()[0]->GetIsEntityAlive()){
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetEntityTurn(1);
  }
  else {
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetEntityTurn(0);}

  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  if (room->GetIsEnemyRoom()){
    for (unsigned int i = 0; i < gameState->GetPlayers().size(); i++){
      room->GetDrawPiles()[i]->SetCards(gameState->GetPlayers()[i]->GetDeck()->GetCards());
      gameState->GetPlayers()[i]->SetEnergy(3);
      gameState->GetPlayers()[i]->SetBuff(Buff(0,0,0,0,0));
      gameState->GetPlayers()[i]->SetDebuff(Debuff(0,0));
      gameState->GetPlayers()[i]->SetBlock(0);
    }
    for (auto& enemy : room->GetEnemies()){
      for(auto skill : enemy->GetSkills()){
        skill->SetTurnsBeforeUse(0, enemy->GetId());
      }
    }
    CommandShuffle commandS(0);
    commandS.Execute(gameState);
    if((int) gameState->GetPlayers().size() == 2 ){
      CommandShuffle commandS(1);
      commandS.Execute(gameState);
    }
    for(int j = 0; j < 5; j++){
      CommandDraw command(0);
      command.Execute(gameState);
    }
  }
}

void CommandEnterRoom::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Enter current room"<<endl;
  gameState->SetIsInsideRoom(false);
}

Json::Value CommandEnterRoom::Serialize () {
  Json::Value val;
  val["typeCmd"] = "EnterRoom";
  return val;
}
 CommandEnterRoom* CommandEnterRoom::Deserialize (Json::Value in){
  return this;
}
