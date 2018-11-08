#include "CommandChangeIntent.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandChangeIntent::CommandChangeIntent (int enemyID, int intent): enemyID(enemyID), intent(intent){}

CommandChangeIntent::CommandChangeIntent (){}

void CommandChangeIntent::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
  for (auto& enemy : enemies){
    if (enemy.get()->GetId() == enemyID){
      enemy.get()->SetIntent(intent);
    }
  }
}

void CommandChangeIntent::Undo (std::shared_ptr<state::GameState>& gameState){
  //TODO: How to undo it ?
}
