
#include "EnemyRoom.h"
using namespace state;

EnemySkill::EnemySkill ()
{

}

EnemySkill::~EnemySkill ()
{

}

EnemySkill::EnemySkill (int attack, int block, Buff buffs,
   Debuff debuffs, std::string intentimage, int cooldown){
     this -> attack = attack;
     this -> block = block;
     this -> buff = buffs;
     this -> debuff = debuffs;
     this -> intentImage = intentimage;
     this -> cooldown = cooldown;
     turnsBeforeUse = 0;
   }



//enemySkill();
int EnemySkill::GetAttack (){
  return attack;
}
void EnemySkill::SetAttack (int newAttack){
  attack = newAttack;
}
int EnemySkill::GetBlock (){
  return block;
}
void EnemySkill::SetBlock (int newBlock){
  block = newBlock;
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
