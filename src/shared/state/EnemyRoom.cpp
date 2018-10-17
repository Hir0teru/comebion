#include "EnemyRoom.h"

using namespace state;


EnemyRoom::~EnemyRoom()
{

}

EnemyRoom::EnemyRoom (int element, std::vector<std::shared_ptr<Enemy>> enemies): Room(element, false, true, false), enemies(enemies), turn(0), entityTurn(0), isGameLost(false)
{

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
  bool res = true;
  int i = 0;
  while (res && i < int( drawPileVector.size())){
    if (drawPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
          throw "DeckParts too big";
          res = false;
        }
    }
  if (res){
    this->drawPiles = drawPileVector;
  }
}

void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DeckParts>> discardPileVector){
  bool res = true;
  int i = 0;
  while (res && i < int(discardPileVector.size())){
    if (discardPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
          throw "DeckParts too big";
          res = false;
        }
    }
  if (res){
    this->discardPiles = discardPileVector;
  }
}

void EnemyRoom::SetHands (std::vector<std::shared_ptr<DeckParts>> handVector){
  bool res = true;
  int i = 0;
  while (res && i < int(handVector.size())){
    if (handVector[i]->GetSize() > this->hands[i]->GetSizeMax()){
          throw "DeckParts too big";
          res = false;
        }
    }
  if (res){
    this->hands = handVector;
  }
}
