#include "CommandAddBlock.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAddBlock::CommandAddBlock (int block, int entityID): block(block), entityID(entityID)
{

}

CommandAddBlock::CommandAddBlock (){}

void CommandAddBlock::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Add "<<block<<" block to entity "<<entityID<<endl;
  PlayerManager* PM = PlayerManager::instance();
  float tmpblock = block;
  if (entityID < 2){
    if((*PM)[entityID] -> GetDebuff(). GetBlockMinus() > 0 ){
      tmpblock = tmpblock/2.;
    }
    if((*PM)[entityID] -> GetBuff().GetBlockPlus() > 0 ){
      tmpblock = tmpblock * 1.5;
    }
    block = (int) tmpblock;
    (*PM)[entityID]->SetBlock((*PM)[entityID]->GetBlock() + block);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    float tmpblock = enemies[entityID - 2] -> GetStatBlock() + block;
    if(enemies[entityID - 2] -> GetDebuff(). GetBlockMinus() > 0 ){
      tmpblock = tmpblock/2.;
    }
    if(enemies[entityID - 2] -> GetBuff().GetBlockPlus() > 0 ){
      tmpblock = tmpblock * 1.5;
    }
    enemies[entityID - 2] ->SetBlock((int) tmpblock);
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
