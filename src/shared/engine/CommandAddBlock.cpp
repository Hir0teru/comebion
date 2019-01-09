#include "CommandAddBlock.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAddBlock::CommandAddBlock (int block, int entityID, int target): block(block), entityID(entityID), target(target)
{

}

CommandAddBlock::CommandAddBlock (){}

void CommandAddBlock::Execute (std::shared_ptr<state::GameState>& gameState){
  if(block > 0 ){
    PlayerManager* PM = PlayerManager::instance();
      int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    float tmpblock;
    if (entityID < 2){
      tmpblock = block + (*PM)[entityID] -> GetStatBlock();
      if((*PM)[entityID] -> GetDebuff(). GetBlockMinus() > 0 ){
        tmpblock = tmpblock/2.;
      }
      if((*PM)[entityID] -> GetBuff().GetBlockPlus() > 0 ){
        tmpblock = tmpblock * 1.5;
      }
    } else {
      tmpblock = enemies[entityID - 2] -> GetStatBlock() + block;
      if(enemies[entityID - 2] -> GetDebuff(). GetBlockMinus() > 0 ){
        tmpblock = tmpblock/2.;
      }
      if(enemies[entityID - 2] -> GetBuff().GetBlockPlus() > 0 ){
        tmpblock = tmpblock * 1.5;
      }
    }
    if(target < 2){
      (*PM)[target]->SetBlock((*PM)[target]->GetBlock() + (int) tmpblock);
    } else{
      enemies[target - 2] ->SetBlock( enemies[target - 2] ->GetBlock() + (int) tmpblock);
    }

    cout<<"Add "<<(int)tmpblock<<" block to entity "<<target<<endl;
  } else{
    //cout<<"Add "<<block<<" block to entity "<<target<<endl;

  }
}

void CommandAddBlock::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Add "<<block<<" to entity "<<entityID<<endl;
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetBlock((*PM)[entityID]->GetBlock() - block);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetBlock(enemy.get()->GetBlock() - block);
      }
    }
  }
}



Json::Value CommandAddBlock::Serialize () {
  Json::Value val;
  val["typeCmd"] = "AddBlock";
  val["block"] = block;
  val["entityID"] = entityID;
  val["target"] = target;
  return val;
}
 CommandAddBlock* CommandAddBlock::Deserialize (Json::Value in){
   entityID = in["entityID"].asInt();
   target = in["target"].asInt());
  return this;
}
