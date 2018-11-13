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
  Room* room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  if (room->GetIsEnemyRoom()){
    for (unsigned int i = 0; i < gameState->GetPlayers().size(); i++){
      room->GetDrawPiles()[i]->SetCards(gameState->GetPlayers()[i]->GetDeck()->GetCards());
    }
    CommandShuffle commandS(0);
    commandS.Execute(gameState);
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
