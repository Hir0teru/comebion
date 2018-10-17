#include "InfoPlayer.h"

using namespace state;

InfoPlayer::~InfoPlayer()
{

}

std::string InfoPlayer::GetFirstElement (){
  return firstElement;
}

void InfoPlayer::SetFirstElement (std::string firstElem){
  this->firstElement = firstElem;
}

bool InfoPlayer::GetPlayerControlledByAI (){
  return playerControlledByAI;
}

void InfoPlayer::SetPlayerControlledByAI (bool controlledByAI){
  this->playerControlledByAI = controlledByAI;
}
