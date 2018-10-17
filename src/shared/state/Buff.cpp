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
void Buff::SetAttackPlus (int newAttackPlus);
int GetHeal (){return heal;}
void SetHeal (int newHeal){
  heal = newHeal;
}
int GetEvade (){return evade;}
void SetEvade (int newEvade){
  evade = newEvade;
}
int GetRetaliate (){return retaliate;}
void SetRetaliate (int newRetaliate){
  retaliate = newRetaliate;
}
// Setters and Getters
};

};
