#include "CommandChangeElement.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeElement::CommandChangeElement (int entityID, int element): entityID(entityID), element(element), previousElement(0){}

CommandChangeElement::CommandChangeElement (){}

void CommandChangeElement::Execute (std::shared_ptr<state::GameState>& gameState){
  if (entityID >= 0){
    cout<<"Change element of entity "<<entityID<<" to "<<element<<endl;
    if (entityID < 2){
      PlayerManager* PM = PlayerManager::instance();
      previousElement = (*PM)[entityID]->GetElement();
      (*PM)[entityID]->SetElement(element);
    } else {
      int floorNb = gameState->GetMap()->GetCurrentFloor();
      std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

      for (auto& enemy : enemies){
        if (enemy.get()->GetId() == entityID){
          previousElement = enemy.get()->GetElement();
          enemy.get()->SetElement(element);
        }
      }
    }
  }
}

void CommandChangeElement::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change element of entity "<<entityID<<" to "<<element<<endl;
  if (entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    (*PM)[entityID]->SetElement(previousElement);
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        enemy.get()->SetElement(previousElement);
      }
    }
  }
}


Json::Value CommandChangeElement::Serialize () {
  Json::Value val;
  val["typeCmd"] = "ChangeElement";
  val["entityID"] = entityID;
  val["element"] = element;
  val["previousElement"] = previousElement;
  return val;
}
 CommandChangeElement* CommandChangeElement::Deserialize (Json::Value in){
   entityID = in["entityID"].asInt();
   element = in["element"].asInt();
   previousElement = in["previousElement"].asInt();
  return this;
}
