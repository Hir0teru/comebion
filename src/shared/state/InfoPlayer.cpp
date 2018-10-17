#include "InfoPlayer.h"

using namespace state;

InfoPlayer::~InfoPlayer()
{

}

int InfoPlayer::GetFirstElement (){
  return firstElement;
}

void InfoPlayer::SetFirstElement (int firstElem){
  this->firstElement = firstElem;
}

bool InfoPlayer::GetPlayerControlledByAI (){
  return playerControlledByAI;
}

void InfoPlayer::SetPlayerControlledByAI (bool controlledByAI){
  this->playerControlledByAI = controlledByAI;
}
