#include "Debuff.h"

using namespace state;

std::string Debuff::GetName (){
  return name;
}

int Debuff::GetNbTurn (){
  return nbTurn;
}

void Debuff::SetNbTurn (int newNbTurn){
  this->nbTurn = newNbTurn;
}
