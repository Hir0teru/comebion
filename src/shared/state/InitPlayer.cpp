#include "InitPlayer.h"

using namespace state;

std::string InitPlayer::GetFirstElement (){
  return firstElement;
}

void InitPlayer::SetFirstElement (std::string firstElem){
  this->firstElement = firstElem;
}

bool InitPlayer::GetPlayerControlledByAI (){
  return playerControlledByAI;
}

void InitPlayer::SetPlayerControlledByAI (bool controlledByAI){
  this->playerControlledByAI = controlledByAI;
}
