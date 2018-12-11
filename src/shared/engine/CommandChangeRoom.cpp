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
  if (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetNextRoom()){
    gameState->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetNextRoom());

    //reset player's turn
    if((int)gameState->GetPlayers().size() == 2 && !gameState->GetPlayers()[0]->GetIsEntityAlive()){
      gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetEntityTurn(1);
    }
    else {gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetEntityTurn(0);}
  } else if(floorNb == 4){
    std::cout << "Fin du jeu, bravo! Vous avez encore sauvé le monde!" <<std::endl;
  } else{
    floorNb ++;
    gameState->GetMap()->SetCurrentFloor(floorNb);
    gameState->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(gameState->GetMap()->GetFloors()[floorNb]->GetFirstRoom());
    for(auto player :gameState->GetPlayers()){
      player->SetLife(player->GetMaxLife());
    }
  }
}

void CommandChangeRoom::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Going to next room"<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  std::shared_ptr<Room> actual_currentRoom = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
  std::shared_ptr<Room>  currentRoom = gameState->GetMap()->GetFloors()[floorNb]->GetFirstRoom();
  if(actual_currentRoom != currentRoom){ // si on ne vient pas de changer de floor
    while (currentRoom->GetNextRoom() != actual_currentRoom){
      currentRoom = currentRoom->GetNextRoom();
    }
    gameState->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(currentRoom);
  } else if(floorNb > 0){
    floorNb --;
    currentRoom = gameState->GetMap()->GetFloors()[floorNb]->GetFirstRoom();
    while (currentRoom->GetNextRoom() ){
      currentRoom = currentRoom->GetNextRoom();
    }
    gameState->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(currentRoom);
  }
}
