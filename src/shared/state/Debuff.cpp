#include "Debuff.h"
#include <iostream>
using namespace state;



Debuff::Debuff(){}

Debuff::Debuff(int blockMinus, int attackMinus){
  this -> blockMinus = blockMinus;
  this -> attackMinus = attackMinus;
}

Debuff::~Debuff(){}

int Debuff::GetBlockMinus (){return blockMinus;}
void Debuff::SetBlockMinus (int newBlockMinus){
  blockMinus = newBlockMinus;
}
int Debuff::GetAttackMinus (){return attackMinus;}
void Debuff::SetAttackMinus (int newAttackMinus){
  attackMinus = newAttackMinus;
}
