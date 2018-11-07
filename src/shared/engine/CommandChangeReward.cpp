#include "CommandChangeReward.h"
#include "state/Enemy.h"

using namespace engine;



CommandChangeReward::CommandChangeReward (){
  enemyID = 2;
}
CommandChangeReward::CommandChangeReward (int enemyID){
  if(enemyID >=2 && enemyID <5){
    this -> enemyID = enemyID;
  }
}
void CommandChangeReward::Execute (std::shared_ptr<state::GameState>& gameState){
  if(enemyID >=2 && enemyID <5){
    int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
    std::unique_ptr<state::Enemy>& enemy= gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[enemyID - 2];
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> SetReward(enemy -> GetReward());
  }
}
void CommandChangeReward::Undo (std::shared_ptr<state::GameState>& gameState){

}
