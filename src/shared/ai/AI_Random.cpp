#include "AI_Random.h"
#include "engine/CommandEnterRoom.h"
#include "engine/CommandHeal.h"
#include "engine/CommandChangeStat.h"
#include "engine/CommandAddCard.h"
#include "engine/CommandExitRoom.h"
#include "engine/CommandRemoveCard.h"
#include <iostream>

using namespace ai;
using namespace state;
using namespace engine;


AI_Random::AI_Random (){}
AI_Random::AI_Random (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityID){
  gameState = gameState;
  moteur = moteur;
  if(entityID >=0 && entityID < 2){
    entityID = entityID;
  } else entityID = 0;

}


std::vector<std::shared_ptr<engine::Command>> AI_Random::GetPossibleCommands (){
  std::vector<std::shared_ptr<engine::Command>> possibleCommands;

  if (gameState->GetRules()->GetIsGameLost()){
    std::cout << "you're dead, deal with it" << std::endl;
  } else if (!gameState->GetIsInsideRoom()){
    possibleCommands.push_back(std::make_shared<engine::CommandEnterRoom>());
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::shared_ptr<Room> room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
    if (room->GetIsSleepRoom()){
      possibleCommands.push_back(std::make_shared<engine::CommandHeal>(room->GetHeal(), entityID));
      possibleCommands.push_back(std::make_shared<engine::CommandChangeStat>(gameState->GetPlayers()[entityID]->GetStatAttack() + 2,gameState->GetPlayers()[entityID]->GetStatBlock() + 2,  entityID));
    } else if (room->GetIsSpecialTrainingRoom()) {
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 0, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 1, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 2, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));

    } else { //enemyroom
      possibleCommands.push_back(std::make_shared<engine::CommandNextEntity>());
      
    }
  }
  return possibleCommands;
}


std::shared_ptr<engine::Command> AI_Random::Play (){
  std::vector<std::shared_ptr<engine::Command>> commands = GetPossibleCommands();
  int index = rand() % (int) commands.size();
  std::shared_ptr<Command> command_chosen = commands[index];

  int floorNb = gameState->GetMap()->GetCurrentFloor();
  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

  if (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom() || gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom()) {
    command_chosen.Execute(gameState);
    CommandExitRoom command;
    command.Execute();
  } else {
    command_chosen.Execute(gameState);
  }
}
