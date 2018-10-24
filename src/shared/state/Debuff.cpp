#include "Debuff.h"
#include <iostream>
using namespace state;



Debuff::Debuff(){
  blockMinus = 0;
  attackMinus = 0;
}

Debuff::Debuff(int blockMinus, int attackMinus){
  if (blockMinus < 0){
    this -> blockMinus = 0;
  }
  else{
    this -> blockMinus = blockMinus;
  }
  if (attackMinus < 0){
    this -> attackMinus = 0;
  }
  else{
    this -> attackMinus = attackMinus;
  }
}

Debuff::~Debuff(){
}

int Debuff::GetBlockMinus (){return blockMinus;}
void Debuff::SetBlockMinus (int newBlockMinus){
  if (newBlockMinus < 0){
    this -> blockMinus = 0;
  }
  else{
    this -> blockMinus = newBlockMinus;
  }
}
int Debuff::GetAttackMinus (){return attackMinus;}
void Debuff::SetAttackMinus (int newAttackMinus){
  if (newAttackMinus < 0){
    this -> attackMinus = 0;
  }
  else{
    this -> attackMinus = newAttackMinus;
  }
}
