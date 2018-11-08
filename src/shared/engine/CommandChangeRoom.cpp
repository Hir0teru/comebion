#include "CommandChangeRoom.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeRoom::CommandChangeRoom (){}

void CommandChangeRoom::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Going to next room"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  gameState->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetNextRoom());
}

void CommandChangeRoom::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Going to next room"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  Room* actual_currentRoom = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom().get();
  Room* currentRoom = gameState->GetMap()->GetFloors()[floorNb]->GetFirstRoom().get();
  while (currentRoom->GetNextRoom().get() != actual_currentRoom){
    currentRoom = currentRoom->GetNextRoom().get();
  }
}
