#include "CommandDie.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandDie::CommandDie (int entityID): entityID(entityID){}

CommandDie::CommandDie (){}

void CommandDie::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Entity "<<entityID<<" died"<<endl;
  Entity* selected_entity = nullptr;
  if (entityID >= 0 && entityID < 2){
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

  selected_entity->SetIsEntityAlive(false);
}

void CommandDie::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Entity "<<entityID<<" died"<<endl;
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

  selected_entity->SetIsEntityAlive(true);
}


Json::Value CommandDie::Serialize () {
  Json::Value val;
  val["typeCmd"] = "Die";
  val["entityID"] = entityID;
  return val;
}
 CommandDie* CommandDie::Deserialize (Json::Value in){
   entityID = in["entityID"].asInt();
  return this;
}
