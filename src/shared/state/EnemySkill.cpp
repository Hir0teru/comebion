
#include "EnemyRoom.h"
#include <iostream>

using namespace state;

EnemySkill::EnemySkill ()
{

}

EnemySkill::EnemySkill (int attack, int heal, int block, std::unique_ptr<Buff> buff,
   std::unique_ptr<Debuff> debuff, std::string intentimage, int cooldown, int target){
     if (attack < 0) {
       this->attack = 0;
     }
     else{
       this->attack = attack;
     }
     if (block < 0){
       this->block = 0;
     } else{
       this->block = block;
     }
     if (heal < 0){
       this->heal = 0;
     } else{
       this->heal = heal;
     }
     this->buff = std::move(buff);
     this->debuff = std::move(debuff);
     this->intentImage = intentimage;
     if (cooldown < 0){
       this->cooldown = 0;
     }
     else {
       this->cooldown = cooldown;
     }

     if (target < 0 or target > 3){
       throw std::out_of_range("Invalid target");
     } else {
       this->target = target;
     }
     turnsBeforeUse = 0;
   }



//enemySkill();
int EnemySkill::GetAttack (){
  return attack;
}
void EnemySkill::SetAttack (int newAttack){
  if (newAttack < 0) {
    this->attack = 0;
  }
  else{
    this->attack = newAttack;
  }
}
int EnemySkill::GetBlock (){
  return block;
}
void EnemySkill::SetBlock (int newBlock){
  if (newBlock < 0){
    this->block = 0;
  } else{
    this->block = newBlock;
  }
}
Buff* EnemySkill::GetBuff (){
  return buff.get();
}

Debuff* EnemySkill::GetDebuff (){
  return debuff.get();
}
std::string EnemySkill::GetIntentImage (){
  return intentImage;
}
int EnemySkill::GetCooldown (){
  return cooldown;
}
int EnemySkill::GetTurnsBeforeUse (){
  return turnsBeforeUse;
}
void EnemySkill::SetTurnsBeforeUse (int newTurnsBU){
  turnsBeforeUse = newTurnsBU;
}

int EnemySkill::GetTarget(){
  return target;
}

int EnemySkill::GetHeal(){
  return heal;
}
