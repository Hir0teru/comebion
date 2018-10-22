
#include "EnemyRoom.h"
#include <iostream>

using namespace state;

EnemySkill::EnemySkill ()
{

}

EnemySkill::~EnemySkill ()
{

}

EnemySkill::EnemySkill (int attack, int heal, int block, std::shared_ptr<Buff> buffs,
   std::shared_ptr<Debuff> debuffs, std::string intentimage, int cooldown, int target) : buff(buffs), debuff(debuffs){
     if (attack < 0) {
       std::cout << "Attack cannot be negative, setting to 0." <<std::endl;
       this -> attack = 0;
     }
     else{
       this -> attack = attack;
     }
     if (block < 0){
       std::cout << "block cannot be negative, setting to 0." << std::endl;
       this -> block = 0;
     } else{
       this -> block = block;
     }
     if (heal < 0){
       std::cout << "heal cannot be negative, setting to 0." << std::endl;
       this -> heal = 0;
     } else{
       this -> heal = heal;
     }
     // this->buff = buffs;
     // this -> debuff = debuffs;
     this -> intentImage = intentimage;
     if (cooldown < 0){
       std::cout << "Cooldown cannot be negative, setting to 0;" << std::endl;
       this-> cooldown = 0;
     }
     else {
       this -> cooldown = cooldown;
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
    std::cout << "Attack cannot be negative, setting to 0." <<std::endl;
    this -> attack = 0;
  }
  else{
    this -> attack = newAttack;
  }
}
int EnemySkill::GetBlock (){
  return block;
}
void EnemySkill::SetBlock (int newBlock){
  if (newBlock < 0){
    std::cout << "block cannot be negative, setting to 0." << std::endl;
    this -> block = 0;
  } else{
    this -> block = newBlock;
  }
}
std::shared_ptr<Buff> EnemySkill::GetBuffs (){
  return buff;
}

std::shared_ptr<Debuff> EnemySkill::GetDebuffs (){
  return debuff;
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
