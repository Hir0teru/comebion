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
  isGameLost = lost;
}

void EnemyRoom::SetDrawPiles (std::vector<std::shared_ptr<DrawPile>> drawPileVector){
  drawPiles = drawPileVector;
}

void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DiscardPile>> discardPileVector){
  discardPiles = discardPileVector;
}

void EnemyRoom::SetHand (std::vector<std::shared_ptr<Hand>> handVector){
  hands = handVector;
}
