#include "EnemyRoom.h"

using namespace state;


EnemyRoom::~EnemyRoom()
{

}

EnemyRoom::EnemyRoom (int element, std::vector<std::shared_ptr<Enemy>> enemies, std::vector<std::shared_ptr<DeckParts>> drawPiles): Room(element, false, true, false), enemies(enemies), drawPiles(drawPiles), turn(0), entityTurn(0), isGameLost(false)
{
  hands.reserve(2);
  discardPiles.reserve(2);
}

int EnemyRoom::GetTurn (){
  return turn;
}

int EnemyRoom::GetEntityTurn (){
  return entityTurn;
}

bool EnemyRoom::GetIsGameLost (){
  return isGameLost;
}

void EnemyRoom::SetIsGameLost (bool lost){
  this->isGameLost = lost;
}

std::vector<std::shared_ptr<DeckParts>> EnemyRoom::GetDrawPiles (){
  return drawPiles;
}

std::vector<std::shared_ptr<DeckParts>> EnemyRoom::GetDiscardPiles (){
  return discardPiles;
}

std::vector<std::shared_ptr<DeckParts>> EnemyRoom::GetHands (){
  return hands;
}

void EnemyRoom::SetDrawPiles (std::vector<std::shared_ptr<DeckParts>> drawPileVector){
  this->drawPiles = drawPileVector;
}

void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DeckParts>> discardPileVector){
  this->discardPiles = discardPileVector;
}

void EnemyRoom::SetHands (std::vector<std::shared_ptr<DeckParts>> handVector){
  this->hands = handVector;
}
