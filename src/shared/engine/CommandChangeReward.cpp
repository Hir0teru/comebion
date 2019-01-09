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
    this->enemyID = enemyID;
  }
}

void CommandChangeReward::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Change reward of current room to reward of enemy "<<enemyID<<endl;
  if(enemyID >=2 && enemyID <5){
    int floorNb =  gameState->GetMap()->GetCurrentFloor();
    std::unique_ptr<state::Enemy>& enemy = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[enemyID - 2];
    previousReward = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetReward();
    gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetReward(enemy->GetReward());
  }
}
void CommandChangeReward::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change reward of current room to reward of enemy "<<enemyID<<endl;
}

Json::Value CommandChangeReward::Serialize () {
  Json::Value val;
  // val["typeCmd"] = "ChangeReward";
  // val["enemyID"] = enemyID;
  // if(previousReward.size()>0){ // serializing only with the name, the card manager will provide the rest
  //   val["card1"] = previousReward[0]->GetName();
  //   val["card2"] = previousReward[1]->GetName();
  //   val["card3"] = previousReward[2]->GetName();
  // } else val["card1"] = "Null";

  return val;
}
 CommandChangeReward* CommandChangeReward::Deserialize (Json::Value in){
   // enemyID = in["enemyID"].asInt();
   // if(in["card1"].compare("Null")!=0){
   //   previousReward.clear();
   //   CardManager* CM = CardManager::instance();
   //   int i=0;
   //   bool res = false;
   //   while(!res && (*CM)[i]){ // will change the original order of the cards but it doesn't matter for the gameplay
   //     if((*CM)[i]->GetName().compare(in["card1"].asString()) == 0){
   //       previousReward.push_back((*CM)[i]);
   //     }
   //     if((*CM)[i]->GetName().compare(in["card2"].asString()) == 0){
   //       previousReward.push_back((*CM)[i]);
   //     }
   //     if((*CM)[i]->GetName().compare(in["card3"].asString()) == 0){
   //       previousReward.push_back((*CM)[i]);
   //     }
   //     if(previousReward.size() == 3) { res = true;}
   //     i++;
   //   }
   //   if(!res){
   //     std::cout << "deserialization of changeReward might have caused error with previousReward" <<std::endl;
   //   }
   //
   // }
  return this;
}
