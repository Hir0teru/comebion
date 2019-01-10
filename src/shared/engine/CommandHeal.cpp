#include "CommandHeal.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandHeal::CommandHeal (int heal, int entityID): heal(heal), entityID(entityID)
{

}

CommandHeal::CommandHeal (){}

void CommandHeal::Execute (std::shared_ptr<state::GameState>& gameState){
  if(heal > 0){
    cout<<"Heal entity "<<entityID<<" of "<<heal<<" hp"<<endl;
    if (entityID >= 0 && entityID < 2){
      PlayerManager* PM = PlayerManager::instance();
      (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() + heal);
    } else {
      int floorNb = gameState->GetMap()->GetCurrentFloor();
      std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

      for (auto& enemy : enemies){
        if (enemy.get()->GetId() == entityID){
          enemy.get()->SetLife(enemy.get()->GetLife() + heal);
        }
      }
    }
  }
}

void CommandHeal::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Heal entity "<<entityID<<" of "<<heal<<" hp"<<endl;
  if (entityID >= 0 && entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetLife((*PM)[entityID]->GetLife() - heal);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetLife(enemy.get()->GetLife() - heal);
      }
    }
  }
}

Json::Value CommandHeal::Serialize () {
  Json::Value val;
  val["typeCmd"] = "Heal";
  val["entityID"] = entityID;
  val["heal"] = heal;
  return val;
}
 CommandHeal* CommandHeal::Deserialize (Json::Value in){
   entityID = in["entityID"].asInt();
   heal = in["heal"].asInt();
  return this;
}
