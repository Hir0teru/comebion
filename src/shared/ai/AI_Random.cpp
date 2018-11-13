#include "AI_Random.h"


using namespace ai;


AI_Random::AI_Random (){}
AI_Random::AI_Random (std::shared_ptr<state::GameState> gameState, std::shared_ptr<engine::Moteur> moteur, int entityNb){
  gameState = gameState;
  moteur = moteur;
  if(entityNb >=0 && entityNb < 2){
    entityNb = entityNb;
  } else entityNb = 0;

}
std::vector<std::shared_ptr<engine::Command>> AI_Random::GetPossibleCommands (){
  std::vector<std::shared_ptr<engine::Command>> possibleCommands;
  if (gameState -> GetIsGameLost()){
    std::cout << "you're dead, deal with it" << std::endl;
  } else if (!gameState -> GetMap() -> GetIsInsideRoom()){
    possibleCommands.push_back(std::make_shared<engine::CommandEnterRoom);
  } else{
    int floorNb = gameState -> GetMap() -> GetCurrentFloor();
    std::shared_ptr<Room> room = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom();
    if (room -> GetIsSleepRoom()){
      possibleCommands.push_back(std::make_shared<engine::CommandHeal>(room -> GetHeal(), entityNb));
      possibleCommands.push_back(std::make_shared<engine::CommandChangeStat>(gameState -> GetPlayers()[entityNb] -> GetStatAttack() + 2,gameState -> GetPlayers()[entityNb] -> GetStatBlock() + 2,  entityNb));
    } else if(room -> GetIsSpecialTrainingRoom()){
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 0, gameState -> GetPlayers()[entityID] -> GetDeck() -> GetSize() == 15));
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 1, gameState -> GetPlayers()[entityID] -> GetDeck() -> GetSize() == 15));
      possibleCommands.push_back(std::make_shared<engine::CommandAddCard>(entityID, 2, gameState -> GetPlayers()[entityID] -> GetDeck() -> GetSize() == 15));
      possibleCommands.push_back(std::make_shared<engine::CommandExitRoom>);
    } else{ //enemyroom
      
    }
  }
}
std::shared_ptr<engine::Command> AI_Random::ChooseCommand (){
  std::vector<std::shared_ptr<engine::Command>> commands = GetPossibleCommands();
  int index = rand() % (int) commands.size();
  return commands[index];
}
void AI_Random::ExecuteCommand(std::shared_ptr<engine::Command> command){

}
