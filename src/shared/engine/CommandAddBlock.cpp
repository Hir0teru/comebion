#include "CommandAddBlock.h"
#include <iostream>
using namespace state;

CommandAddBlock (int block, int entityID): block(block), entityID(entityID)
{

}

CommandAddBlock (){}

void Execute (std::shared_ptr<state::GameState>& gameState){
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[i]->SetBlock((*PM)[i]->GetBlock() + block);
  } else {
    int floorNb = rendu->GetGameState()->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState()->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetBlock(enemy.get()->GetBlock() + block);
      }
    }
  }
}
