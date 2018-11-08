#include "CommandChangeElement.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandChangeElement::CommandChangeElement (int entityID, int element): entityID(entityID), element(element){}

CommandChangeElement::CommandChangeElement (){}

void CommandChangeElement::Execute (std::shared_ptr<state::GameState>& gameState){
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetElement(element);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetElement(element);
      }
    }
  }
}

void CommandChangeElement::Undo (std::shared_ptr<state::GameState>& gameState){
  //TODO: How to undo it ?
}
