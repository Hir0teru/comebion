#include "Buff.h"

using namespace state;




Buff::Buff (){}
Buff::Buff (int blockPlus, int attackPlus, int heal, int evade, int retaliate){
  this -> blockPlus = blockPlus;
  this -> attackPlus = attackPlus;
  this -> heal = heal;
  this -> evade = evade;
  this -> retaliate = retaliate;
}
int Buff::GetBlockPlus (){return blockPlus;}
void Buff::SetBlockPlus (int newBlockPlus){
  blockPlus = newBlockPlus;
}
int Buff::GetAttackPlus (){return attackPlus;}
void Buff::SetAttackPlus (int newAttackPlus){
  attackPlus = newAttackPlus;
}
int Buff::GetHeal (){return heal;}
void Buff::SetHeal (int newHeal){
  heal = newHeal;
}
int Buff::GetEvade (){return evade;}
void Buff::SetEvade (int newEvade){
  evade = newEvade;
}
int Buff::GetRetaliate (){return retaliate;}
void Buff::SetRetaliate (int newRetaliate){
  retaliate = newRetaliate;
}
