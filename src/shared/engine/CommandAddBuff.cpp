#include "CommandAddBuff.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandAddBuff::CommandAddBuff (int entityID, state::Buff buff): entityID(entityID), buff(buff)
{

}

CommandAddBuff::CommandAddBuff (){}

void CommandAddBuff::Execute (std::shared_ptr<state::GameState>& gameState){
  if(buff.GetBlockPlus() > 0){
    cout<<" BlockPlus "<< buff.GetBlockPlus()<< endl;
  }
  if(buff.GetAttackPlus() > 0 ){
    cout<<" AttackPlus "<< buff.GetAttackPlus()<< endl;
  }
  if(buff.GetHeal() > 0){
    cout<<" Heal "<< buff.GetHeal()<< endl;
  }
  if(buff.GetEvade() > 0){
    cout<<" Evade "<< buff.GetEvade()<< endl;
  }
  if(buff.GetRetaliate() > 0){
    cout<<" Retaliate "<< buff.GetRetaliate()<< endl;
  }
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
  Buff entity_buff = selected_entity->GetBuff();
  entity_buff.SetBlockPlus(entity_buff.GetBlockPlus() + buff.GetBlockPlus());
  entity_buff.SetAttackPlus(entity_buff.GetAttackPlus() + buff.GetAttackPlus());
  entity_buff.SetHeal(entity_buff.GetHeal() + buff.GetHeal());
  entity_buff.SetEvade(entity_buff.GetEvade() + buff.GetEvade());
  entity_buff.SetRetaliate(entity_buff.GetRetaliate() + buff.GetRetaliate());

  selected_entity->SetBuff(entity_buff);
}

void CommandAddBuff::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Add buff to entity "<<entityID<<endl;
  cout<<" BlockPlus "<< buff.GetBlockPlus()<< endl;
  cout<<" AttackPlus "<< buff.GetAttackPlus()<< endl;
  cout<<" Heal "<< buff.GetHeal()<< endl;
  cout<<" Evade "<< buff.GetEvade()<< endl;
  cout<<" Retaliate "<< buff.GetRetaliate()<< endl;  Entity* selected_entity = nullptr;
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
  Buff entity_buff = selected_entity->GetBuff();
  entity_buff.SetBlockPlus(entity_buff.GetBlockPlus() - buff.GetBlockPlus());
  entity_buff.SetAttackPlus(entity_buff.GetAttackPlus() - buff.GetAttackPlus());
  entity_buff.SetHeal(entity_buff.GetHeal() - buff.GetHeal());
  entity_buff.SetEvade(entity_buff.GetEvade() - buff.GetEvade());
  entity_buff.SetRetaliate(entity_buff.GetRetaliate() - buff.GetRetaliate());

  selected_entity->SetBuff(entity_buff);
}

json_map CommandAddBuff::Serialize () {
  json_map val;
  val["typeCmd"] = "AddBuff";
  val["entityID"] = entityID;
  val["blockPlus"] = buff.GetBlockPlus();
  val["attackPlus"] = buff.GetAttackPlus();
  val["heal"] = buff.GetHeal();
  val["evade"] = buff.GetEvade();
  val["retaliate"] = buff.GetRetaliate();
  return val;
}
 CommandAddBuff* CommandAddBuff::Deserialize ( json_map in){
   entityID = in["entityID"].as<json_int>();
   state::Buff tmpbuff;
   tmpbuff.SetBlockPlus(in["blockPlus"].as<json_int>());
   tmpbuff.SetAttackPlus(in["attackPlus"].as<json_int>());
   tmpbuff.SetHeal(in["heal"].as<json_int>());
   tmpbuff.SetEvade(in["evade"].as<json_int>());
   tmpbuff.SetRetaliate(in["retaliate"].as<json_int>());
   buff = tmpbuff;
  return this;
}
