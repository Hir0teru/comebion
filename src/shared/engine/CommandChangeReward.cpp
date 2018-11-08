#include "CommandChangeReward.h"
#include "state/Enemy.h"
#include <iostream>

using namespace engine;
using namespace std;

CommandChangeReward::CommandChangeReward (){
  enemyID = 2;
}

CommandChangeReward::CommandChangeReward (int enemyID){
  if(enemyID >=2 && enemyID <5){
    this -> enemyID = enemyID;
  }
}

void CommandChangeReward::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Change reward of current room to reward of enemy "<<enemyID<<endl;
  if(enemyID >=2 && enemyID <5){
    int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
    std::unique_ptr<state::Enemy>& enemy= gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[enemyID - 2];
    gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> SetReward(enemy -> GetReward());
  }
}
void CommandChangeReward::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change reward of current room to reward of enemy "<<enemyID<<endl;
}
