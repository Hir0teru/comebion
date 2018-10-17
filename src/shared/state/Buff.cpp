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
  if (newBlockPlus < 0) {
    blockPlus = 0;
  }
  else{
  blockPlus = newBlockPlus;
}
}
int Buff::GetAttackPlus (){return attackPlus;}
void Buff::SetAttackPlus (int newAttackPlus){
  if (newAttackPlus < 0){
    attackPlus = newAttackPlus;
  }
  else{
  attackPlus = newAttackPlus;
}
}
int Buff::GetHeal (){return heal;}
void Buff::SetHeal (int newHeal){
  if (newHeal < 0){
    heal = 0;
  }
  else{
  heal = newHeal;
}
}
int Buff::GetEvade (){return evade;}
void Buff::SetEvade (int newEvade){
  if (newEvade < 0){
    evade = 0;
  }
  else{
  evade = newEvade;
}
}
int Buff::GetRetaliate (){return retaliate;}
void Buff::SetRetaliate (int newRetaliate){
  if (newRetaliate < 0){
    retaliate = 0;
  }
  else {
  retaliate = newRetaliate;
}
}
