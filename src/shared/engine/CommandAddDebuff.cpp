#include "CommandAddDebuff.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;

CommandAddDebuff::CommandAddDebuff (int entityID, state::Debuff debuff): entityID(entityID), debuff(debuff){}

CommandAddDebuff::CommandAddDebuff (){}

void CommandAddDebuff::Execute (std::shared_ptr<state::GameState>& gameState){
  Entity* selected_entity = nullptr;
  if (entityID < 2){
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
  Debuff entity_debuff = selected_entity->GetDebuff();
  entity_debuff.SetBlockMinus(entity_debuff.GetBlockMinus() + debuff.GetBlockMinus());
  entity_debuff.SetAttackMinus(entity_debuff.GetAttackMinus() + debuff.GetAttackMinus());

  selected_entity->SetDebuff(entity_debuff);
}

void CommandAddDebuff::Undo (std::shared_ptr<state::GameState>& gameState){
  Entity* selected_entity = nullptr;
  if (entityID < 2){
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
  Debuff entity_debuff = selected_entity->GetDebuff();
  entity_debuff.SetBlockMinus(entity_debuff.GetBlockMinus() - debuff.GetBlockMinus());
  entity_debuff.SetAttackMinus(entity_debuff.GetAttackMinus() - debuff.GetAttackMinus());

  selected_entity->SetDebuff(entity_debuff);
}