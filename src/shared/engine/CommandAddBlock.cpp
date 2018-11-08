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
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetBlock((*PM)[entityID]->GetBlock() + block);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetBlock(enemy.get()->GetBlock() + block);
      }
    }
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
