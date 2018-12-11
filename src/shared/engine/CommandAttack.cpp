#include "CommandAttack.h"
#include "state/PlayerManager.h"
#include "state/Enemy.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;
// 4 > 3 > 2 > 1
CommandAttack::CommandAttack (int damage, int entityID, int target): damage(damage), entityID(entityID), target(target), entityLife(0), targetLife(0)
{
}

CommandAttack::CommandAttack (){}

void CommandAttack::Execute (std::shared_ptr<state::GameState>& gameState){
  int entityElement = 0;
  int targetElement = 0;
  if(damage > 0){
    PlayerManager* PM = PlayerManager::instance();
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    float tmpdamage;
    if (entityID < 2){
      entityLife = (*PM)[entityID]->GetLife();
      entityElement = (*PM)[entityID]->GetElement();
      tmpdamage = damage + (*PM)[entityID]->GetStatAttack();
      if((*PM)[entityID]->GetDebuff().GetAttackMinus() > 0 ){
        tmpdamage = tmpdamage/2.;
      }
      if((*PM)[entityID]->GetBuff().GetAttackPlus() > 0 ){
        tmpdamage = tmpdamage * 1.5;
      }
    } else {
      entityLife = enemies[entityID - 2]->GetLife();
      entityElement = enemies[entityID - 2]->GetElement();
      tmpdamage = damage + enemies[entityID - 2]->GetStatAttack();
      if(enemies[entityID - 2]->GetDebuff().GetAttackMinus() > 0 ){
        tmpdamage = tmpdamage/2.;
      }
      if(enemies[entityID - 2]->GetBuff().GetAttackPlus() > 0 ){
        tmpdamage = tmpdamage * 1.5;
      }
    }
    if(target < 2){
      targetLife = (*PM)[target]->GetLife();
      targetElement = (*PM)[target]->GetElement();

      // check elements:
      switch(entityElement){
        case 1:
          if (targetElement == 4){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 2){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 2:
          if (targetElement == 1){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 3){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 3:
          if (targetElement == 2){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 4){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 4:
          if (targetElement == 3){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 1){
            tmpdamage = tmpdamage/2.;
          }
          break;
      }


      if((*PM)[target]->GetBuff().GetEvade() <= 0){ // check Evade
        //calculate damage
        int block = (*PM)[target]->GetBlock();
        (*PM)[target]->SetBlock(block - (int)tmpdamage);
        tmpdamage -= block;
        if(tmpdamage > 0){
          (*PM)[target]->SetLife((*PM)[target]->GetLife() - (int)tmpdamage);
          cout<<"Attack entity "<<target<<" with "<<(int)tmpdamage<<"damages"<<endl;
        }
      } else std::cout << target << " evade attack from " << entityID;
        //check retaliate
      int retaliate = (*PM)[target]->GetBuff().GetRetaliate();
      if(retaliate> 0){
        std::cout << target << " retaliate on " << entityID << std::endl;
        if(entityID < 2){
          int block = (*PM)[entityID]->GetBlock();
          (*PM)[entityID]->SetBlock(block - 5);
          retaliate = 5 - block;
          if(retaliate > 0){
            (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() - retaliate);
          }
        } else {
          int block = enemies[entityID - 2]->GetBlock();
          enemies[entityID - 2]->SetBlock(enemies[entityID - 2]->GetBlock() - 5);
          retaliate = 5 - block;
          if(retaliate> 0){
            enemies[entityID -2]->SetLife(enemies[entityID - 2]->GetLife() - retaliate);
          }
        }
      }

    } else {
      targetLife = enemies[target - 2]->GetLife();
      targetElement = enemies[target - 2]->GetElement();

      // check elements:

      switch(entityElement){
        case 1:
          if (targetElement == 4){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 2){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 2:
          if (targetElement == 1){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 3){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 3:
          if (targetElement == 2){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 4){
            tmpdamage = tmpdamage/2.;
          }
          break;
        case 4:
          if (targetElement == 3){
            tmpdamage = tmpdamage * 1.5;
          } else if (targetElement == 1){
            tmpdamage = tmpdamage/2.;
          }
          break;
      }



      if(  enemies[target - 2]->GetBuff().GetEvade() <=0){
        int block = enemies[target - 2]->GetBlock();
        enemies[target - 2]->SetBlock(block - (int)tmpdamage);
        tmpdamage -= block;
        if(tmpdamage> 0){
          enemies[target -2]->SetLife(enemies[target - 2]->GetLife() - (int)tmpdamage);
          cout<<"Attack entity "<<target<<" with "<<(int)tmpdamage<<"damages"<<endl;
        }
      } else std::cout << target << " evade attack from " << entityID;
      int retaliate = enemies[target - 2]->GetBuff().GetRetaliate();
      if(retaliate> 0){
        std::cout << target << " retaliate on " << entityID << std::endl;
        if(entityID < 2){
          int block = (*PM)[entityID]->GetBlock();
          (*PM)[entityID]->SetBlock(block - 5);
          retaliate = 5 - block;
          if(retaliate > 0){
            (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() - retaliate);
          }
        } else{
          int block = enemies[entityID - 2]->GetBlock();
          enemies[entityID - 2]->SetBlock(enemies[entityID - 2]->GetBlock() - 5);
          retaliate = 5 - block;
          if(retaliate> 0){
            enemies[entityID -2]->SetLife(enemies[entityID - 2]->GetLife() - retaliate);
          }
        }
      }
    }
  }
  // else{
  // //cout<<"Attack entity "<<target<<" with "<<(int)damage<<"damages"<<endl;
  // }
}

void CommandAttack::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Attack entity "<<target<<" with "<<damage<<"damages"<<endl;
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetLife(entityLife);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetLife(entityLife);
      }
    }
  }

  if (target < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[target]->SetLife(targetLife);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == target){
        enemy.get()->SetLife(targetLife);
      }
    }
  }
}
