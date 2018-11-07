#include "CommandSetReward.h"

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
      // int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
      // gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> SetReward()
    }
  }
  void Undo (std::shared_ptr<state::GameState>& gameState){}
