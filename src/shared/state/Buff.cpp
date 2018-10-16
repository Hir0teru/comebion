#include "Buff.h"

using namespace state;

std::string Buff::GetName (){
  return name;
}

int Buff::GetNbTurn (){
  return nbTurn;
}

void Buff::SetNbTurn (int newNbTurn){
  this->nbTurn = newNbTurn;
}
