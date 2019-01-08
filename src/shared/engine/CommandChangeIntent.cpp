#include "CommandChangeIntent.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeIntent::CommandChangeIntent (int enemyID, int intent): enemyID(enemyID), intent(intent), previousIntent(0){}

CommandChangeIntent::CommandChangeIntent (){}

void CommandChangeIntent::Execute (std::shared_ptr<state::GameState>& gameState){
  if (enemyID > 1){
    cout<<"Change intent of enemy "<<enemyID<<" to "<<intent<<endl;
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == enemyID){
        enemy.get()->SetIntent(intent);
      }
    }
  }
}

void CommandChangeIntent::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change intent of enemy "<<enemyID<<" to "<<intent<<endl;
  int floorNb = gameState->GetMap()->GetCurrentFloor();
  std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();
  for (auto& enemy : enemies){
    if (enemy.get()->GetId() == enemyID){
      enemy.get()->SetIntent(previousIntent);
    }
  }
}

json_map CommandChangeIntent::Serialize () {
  json_map val;
  val["typeCmd"] = "changeIntent";
  val["enemyID"] = enemyID;
  val["intent"] = intent;
  val["previousIntent"] = previousIntent;
  return val;
}
 CommandChangeIntent* CommandChangeIntent::Deserialize (json_map in){
   enemyID = in["enemyID"].as<json_int>();
   intent = in["intent"].as<json_int>();
   previousIntent = in["previousIntent"].as<json_int>();
  return this;
}
