#include "AI_Random.h"
#include "engine.h"
#include <iostream>

using namespace ai;
using namespace state;
using namespace engine;


AI_Random::AI_Random (){}
AI_Random::AI_Random (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityID){
  this -> gameState = gameState;
  this -> moteur = moteur;
  if(entityID >=0 && entityID < 2){
    this -> entityID = entityID;
  } else entityID = 0;

}


std::vector<std::shared_ptr<engine::Command>> AI_Random::GetPossibleCommands (){
  std::vector<std::shared_ptr<engine::Command>> possibleCommands;

  if (gameState ->  GetRules()->GetIsGameLost()){
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
      possibleCommands.push_back(std::make_shared<engine::CommandNextEntity>());


    } else { //enemyroom
      if(!gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetIsFightWon()){ // keep fighting
        for (int i = 0; i < room -> GetHands()[entityID] -> GetSize(); i++){ // try to play cards
          if(room -> GetHands()[entityID] -> GetCards()[i] -> GetTarget() == 0 || room -> GetHands()[entityID] -> GetCards()[i] -> GetTarget() == 3){
            possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, 0, i));
            if((int)gameState -> GetPlayers().size() == 2 ){
              possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, 1, i));
            }
          } else{
            for(int j = 0; j < (int) room -> GetEnemies().size(); j++){
              possibleCommands.push_back(std::make_shared<engine::CommandPlayCard>(entityID, j+2, i));
            }
          }
        }
        possibleCommands.push_back(std::make_shared<engine::CommandNextEntity>());
      } else{ //fight won
        std::cout << "won the fight, choose reward" << std::endl;
        possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 0, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 1, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 2, gameState->GetPlayers()[entityID]->GetDeck()->GetSize() == 15));
        possibleCommands.push_back(std::make_shared<engine::CommandNextEntity>());
      }
    }
  }
  return possibleCommands;
}


void AI_Random::Play (){
  std::cout << "thinking ..." << std::endl;
  std::vector<std::shared_ptr<engine::Command>> commands = GetPossibleCommands();
  int index = rand() % (int) commands.size();
  std::shared_ptr<Command> command_chosen = commands[index];
  moteur -> AddCommand(command_chosen);

  int floorNb = gameState->GetMap()->GetCurrentFloor();

  if (gameState->GetIsInsideRoom() &&(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom() || gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom())) {
    moteur -> AddCommand(std::make_shared<CommandNextEntity>());
    std::cout << "done thinking!" << std::endl;
  }

  //   command_chosen.Execute(gameState);
  //   CommandExitRoom command;
  //   command.Execute();
  // } else {
    // command_chosen -> Execute(gameState);
  // }
}

std::shared_ptr<engine::Moteur>& AI_Random::GetMoteur(){
  return moteur;
}
