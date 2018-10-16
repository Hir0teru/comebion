#include "EnemyRoom.h"

using namespace state;

int EnemyRoom::GetTurn (){
  return turn;
}

int EnemyRoom::GetEntityTurn (){
  return EntityTurn;
}

bool EnemyRoom::GetIsGameLost (){
  return isGameLost;
}

void EnemyRoom::SetIsGameLost (bool lost){
  this->isGameLost = lost;
}

std::vector<std::shared_ptr<DrawPile>> EnemyRoom::GetDrawPiles (){
  return drawPiles;
}

std::vector<std::shared_ptr<DiscardPile>> EnemyRoom::GetDiscardPiles (){
  return discardPiles;
}

std::vector<std::shared_ptr<Hand>> EnemyRoom::GetHands (){
  return hands;
}

void EnemyRoom::SetDrawPiles (std::vector<std::shared_ptr<DrawPile>> drawPileVector){
  this->drawPiles = drawPileVector;
}

void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DiscardPile>> discardPileVector){
  this->discardPiles = discardPileVector;
}

void EnemyRoom::SetHands (std::vector<std::shared_ptr<Hand>> handVector){
  this->hands = handVector;
}
