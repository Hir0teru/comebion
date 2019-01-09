#include "CommandChangeStat.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeStat::CommandChangeStat (int entityID, int statAttack, int statBlock): entityID(entityID), statAttack(statAttack), statBlock(statBlock), previousStatAttack(0), previousStatBlock(0){}

CommandChangeStat::CommandChangeStat (){}

void CommandChangeStat::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Change stat of entity "<<entityID<<endl;
  cout<<" StatAttack "<< statAttack<< endl;
  cout<<" StatBlock "<< statBlock<< endl;
  Entity* selected_entity = nullptr;
  if (entityID >= 0 && entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    selected_entity = (*PM)[entityID];
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        selected_entity = enemy.get();
      }
    }
  }
  previousStatAttack = selected_entity->GetStatAttack();
  previousStatBlock = selected_entity->GetStatBlock();
  selected_entity->SetStatAttack(statAttack);
  selected_entity->SetStatBlock(statBlock);
}

void CommandChangeStat::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change stat of entity "<<entityID<<endl;
  cout<<" StatAttack "<< statAttack<< endl;
  cout<<" StatBlock "<< statBlock<< endl;
  Entity* selected_entity = nullptr;
  if (entityID >= 0 && entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    selected_entity = (*PM)[entityID];
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        selected_entity = enemy.get();
      }
    }
  }
  selected_entity->SetStatAttack(previousStatAttack);
  selected_entity->SetStatBlock(previousStatBlock);
}


Json::ValueType CommandChangeStat::Serialize () {
  Json::ValueType val;
  val["typeCmd"] = "ChangeStat";
  val["entityID"] = entityID;
  val["statAttack"] = statAttack;
  val["statBlock"] = statBlock;
  val["previousStatAttack"] = previousStatAttack;
  val["previousStatBlock"] = previousStatBlock;
  return val;
}
 CommandChangeStat* CommandChangeStat::Deserialize (Json::ValueType in){
   entityID = in["entityID"].asInt();
   statAttack = in["statAttack"].asInt();
   statBlock = in["statBlock"].asInt();
   previousStatAttack = in["previousStatAttack"].asInt();
   previousStatBlock = in["previousStatBlock"].asInt();
  return this;
}
