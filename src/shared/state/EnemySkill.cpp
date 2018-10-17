
#include "EnemyRoom.h"
#include <iostream>
#include <stdexcept>

using namespace state;

EnemySkill::EnemySkill ()
{

}

EnemySkill::~EnemySkill ()
{

}

EnemySkill::EnemySkill (int attack, int block, Buff buffs,
   Debuff debuffs, std::string intentimage, int cooldown){
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
     this -> buff = buffs;
     this -> debuff = debuffs;
     this -> intentImage = intentimage;
     if (cooldown < 0){
       std::cout << "Cooldown cannot be negative, setting to 0;" << std::endl;
       this-> cooldown = 0;
     }
     else {
       this -> cooldown = cooldown;
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
Buff EnemySkill::GetBuffs (){
  return buff;
}
Debuff EnemySkill::GetDebuffs (){
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
