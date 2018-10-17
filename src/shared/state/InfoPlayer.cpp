#include "InfoPlayer.h"
#include <iostream>

using namespace state;

InfoPlayer::InfoPlayer(){
  firstElement = 1; //0 = None, 1 = Air, 2 = Water, 3 = Earth, 4 = Fire
  playerControlledByAI = false;
}

InfoPlayer::~InfoPlayer(){}

InfoPlayer::InfoPlayer (int firstElement, bool playerControlledByAI){
  if (firstElement < 1 or firstElement > 4) {
    throw "Element not valid";
  } else {
    this->firstElement = firstElement;
  }
  this->playerControlledByAI = playerControlledByAI;
}

int InfoPlayer::GetFirstElement (){
  return firstElement;
}

void InfoPlayer::SetFirstElement (int firstElem){
  if (firstElem < 1 || firstElem > 4) {
    std::cout << "First element unvalid : valid are '0'(none), '1'(air), '2'(water), '3'(earth), '4'(fire)." << std::endl;
    this -> firstElement = 1;
  }
  else{
    this->firstElement = firstElem;
  }
}

bool InfoPlayer::GetPlayerControlledByAI (){
  return playerControlledByAI;
}

void InfoPlayer::SetPlayerControlledByAI (bool controlledByAI){
  if (controlledByAI){
    std::cout << "Player will now be controlled by the AI" << std::endl;
  }
  this->playerControlledByAI = controlledByAI;
}
