#include "CommandAttack.h"
#include "state/PlayerManager.h"
#include "state/Enemy.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAttack::CommandAttack (int damage, int entityID): damage(damage), entityID(entityID)
{

}

CommandAttack::CommandAttack (){}

void CommandAttack::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Attack entity "<<entityID<<" with "<<damage<<"damages"<<endl;
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    int tmpdamage = damage;
    tmpdamage -= (*PM)[entityID]->GetBlock();
    (*PM)[entityID]->SetBlock((*PM)[entityID]->GetBlock() - damage);
    if(tmpdamage > 0){
      (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() - tmpdamage);
    }
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    int tmpdamage = damage;
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
