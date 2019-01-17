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

Json::Value CommandAddBuff::Serialize () {
  Json::Value val;
  val["typeCmd"] = "AddBuff";
  val["entityID"] = entityID;
  val["buff_BP"] = buff.GetBlockPlus();
  val["buff_AP"] = buff.GetAttackPlus();
  val["buff_H"] = buff.GetHeal();
  val["buff_E"] = buff.GetEvade();
  val["buff_R"] = buff.GetRetaliate();
  return val;
}
 CommandAddBuff* CommandAddBuff::Deserialize ( Json::Value in){
   entityID = in["entityID"].asInt();
   state::Buff tmpbuff;
   tmpbuff.SetBlockPlus(in["buff_BP"].asInt());
   tmpbuff.SetAttackPlus(in["buff_AP"].asInt());
   tmpbuff.SetHeal(in["buff_H"].asInt());
   tmpbuff.SetEvade(in["buff_E"].asInt());
   tmpbuff.SetRetaliate(in["buff_R"].asInt());
   buff = tmpbuff;
  return this;
}
