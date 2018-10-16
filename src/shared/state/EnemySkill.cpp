
#include "EnemyRoom.h"
using namespace state;

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
std::vector<std::shared_ptr<Buff>> EnemySkill::GetBuffs (){
  return buffs;
}
std::vector<std::shared_ptr<Debuff>> EnemySkill::GetDebuffs (){
  return debuffs;
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
