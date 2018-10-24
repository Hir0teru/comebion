#include "Buff.h"
#include <iostream>
using namespace state;

Buff::Buff (){
  blockPlus = 0;
  attackPlus = 0;
  heal = 0;
  evade = 0;
  retaliate = 0;
}

Buff::Buff (int blockPlus, int attackPlus, int heal, int evade, int retaliate){
  if (blockPlus < 0){
    this -> blockPlus = 0;
  }
  else{
    this -> blockPlus = blockPlus;
  }
  if (attackPlus < 0){
    this -> attackPlus = 0;
  }
  else{
    this -> attackPlus = attackPlus;
  }
  if (heal < 0){
    this -> heal = 0;
  }
  else{
    this -> heal = heal;
  }
  if (evade < 0){
    this -> evade = 0;
  }
  else{
    this -> evade = evade;
  }
  if (retaliate < 0){
    this -> retaliate = 0;
  }
  else{
    this -> retaliate = retaliate;
  }
}
Buff::~Buff(){
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
