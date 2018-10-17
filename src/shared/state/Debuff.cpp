#include "Debuff.h"
#include <iostream>
using namespace state;



Debuff::Debuff(){
  blockMinus = 0;
  attackMinus = 0;
}

Debuff::Debuff(int blockMinus, int attackMinus){
  if (blockMinus < 0){
    std::cout<<"error with blockMinus "<< blockMinus <<std::endl;
    this -> blockMinus = 0;
  }
  else{
    this -> blockMinus = blockMinus;
  }
  if (attackMinus < 0){
    std::cout<<"error with attackMinus "<< attackMinus <<std::endl;
    this -> attackMinus = 0;
  }
  else{
    this -> attackMinus = attackMinus;
  }
}

Debuff::~Debuff(){
  std::cout<<"Debuff destroyed"<<std::endl;
}

int Debuff::GetBlockMinus (){return blockMinus;}
void Debuff::SetBlockMinus (int newBlockMinus){
  if (newBlockMinus < 0){
    std::cout<<"error with blockMinus "<< newBlockMinus <<std::endl;
    this -> blockMinus = 0;
  }
  else{
    this -> blockMinus = newBlockMinus;
  }
}
int Debuff::GetAttackMinus (){return attackMinus;}
void Debuff::SetAttackMinus (int newAttackMinus){
  if (newAttackMinus < 0){
    std::cout<<"error with attackMinus "<< newAttackMinus <<std::endl;
    this -> attackMinus = 0;
  }
  else{
    this -> attackMinus = newAttackMinus;
  }
}
