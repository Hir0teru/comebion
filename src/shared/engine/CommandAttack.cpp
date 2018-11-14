#include "CommandAttack.h"
#include "state/PlayerManager.h"
#include "state/Enemy.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;
// 4 > 3 > 2 > 1
CommandAttack::CommandAttack (int damage, int entityID, int target): damage(damage), entityID(entityID), target(target)
{

}

CommandAttack::CommandAttack (){}

void CommandAttack::Execute (std::shared_ptr<state::GameState>& gameState){
  if(damage > 0){
    PlayerManager* PM = PlayerManager::instance();
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    float tmpdamage;
    if (entityID < 2){
      tmpdamage = damage + (*PM)[entityID] -> GetStatAttack();
      if((*PM)[entityID] -> GetDebuff().GetAttackMinus() > 0 ){
        tmpdamage = tmpdamage/2.;
      }
      if((*PM)[entityID] -> GetBuff().GetAttackPlus() > 0 ){
        tmpdamage = tmpdamage * 1.5;
      }
      tmpdamage -= (*PM)[entityID]->GetBlock();

    } else {
      tmpdamage = damage + enemies[entityID - 2] -> GetStatAttack();
      if(enemies[entityID - 2] -> GetDebuff().GetAttackMinus() > 0 ){
        tmpdamage = tmpdamage/2.;
      }
      if(enemies[entityID - 2] -> GetBuff().GetAttackPlus() > 0 ){
        tmpdamage = tmpdamage * 1.5;
      }
    }
    if(target < 2){
      int block = (*PM)[target]->GetBlock();
      (*PM)[target]->SetBlock(block - (int)tmpdamage);
      tmpdamage -= block;
      if(tmpdamage > 0){
        (*PM)[target]->SetLife((*PM)[target]->GetLife() - (int)tmpdamage);
      }
    } else{
      int block = enemies[target - 2]->GetBlock();
      enemies[target - 2]->SetBlock(enemies[target - 2]->GetBlock() - (int)tmpdamage);
      if(tmpdamage - block> 0){
        enemies[target -2]->SetLife(enemies[target - 2]->GetLife() - (int)tmpdamage + block);
      }
    }
  cout<<"Attack entity "<<target<<" with "<<(int)tmpdamage<<"damages"<<endl;
  } else{
  cout<<"Attack entity "<<target<<" with "<<(int)damage<<"damages"<<endl;
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
