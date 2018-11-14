#include "CommandAttack.h"
#include "state/PlayerManager.h"
#include "state/Enemy.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;
// 4 > 3 > 2 > 1
CommandAttack::CommandAttack (int damage, int entityID): damage(damage), entityID(entityID)
{

}

CommandAttack::CommandAttack (){}

void CommandAttack::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Attack entity "<<entityID<<" with "<<damage<<"damages"<<endl;
  PlayerManager* PM = PlayerManager::instance();
  if (entityID < 2){
    float tmpdamage = damage + (*PM)[entityID] -> GetStatAttack();
    if((*PM)[entityID] -> GetDebuff().GetAttackMinus() > 0 ){
      tmpdamage = tmpdamage/2.;
    }
    if((*PM)[entityID] -> GetBuff().GetAttackPlus() > 0 ){
      tmpdamage = tmpdamage * 1.5;
    }
    tmpdamage -= (*PM)[entityID]->GetBlock();
    (*PM)[entityID]->SetBlock((*PM)[entityID]->GetBlock() - damage);
    if(tmpdamage > 0){
      (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() - (int)tmpdamage);
    }
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    float tmpdamage = damage + enemies[entityID - 2] -> GetStatAttack();
    if(enemies[entityID - 2] -> GetDebuff().GetAttackMinus() > 0 ){
      tmpdamage = tmpdamage/2.;
    }
    if(enemies[entityID - 2] -> GetBuff().GetAttackPlus() > 0 ){
      tmpdamage = tmpdamage * 1.5;
    }
    tmpdamage -= enemies[entityID - 2]->GetBlock();
    enemies[entityID - 2]->SetBlock(enemies[entityID - 2]->GetBlock() - damage);
    if(tmpdamage > 0){
      enemies[entityID -2]->SetLife(enemies[entityID - 2]->GetLife() - tmpdamage);
    }
  }
}

void CommandAttack::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Attack entity "<<entityID<<" with "<<damage<<"damages"<<endl;
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() + damage);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetLife(enemy.get()->GetLife() + damage);
      }
    }
  }
}
