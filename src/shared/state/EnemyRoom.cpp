#include "EnemyRoom.h"

using namespace state;


EnemyRoom::~EnemyRoom()
{

}

EnemyRoom::EnemyRoom (int element, std::vector<std::shared_ptr<Enemy>> enemies): Room(element, false, true, false), turn(0), entityTurn(0), isGameLost(false)
{
  if (enemies.size() <= 0) {
    throw std::invalid_argument("not enough enemies");
  } else if (enemies.size() > 3) {
    throw std::invalid_argument("too many enemies");
  } else {
    this->enemies = enemies;
  }
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
  for(int i = 0; i < int( drawPileVector.size()); i++){
    if (!drawPileVector[i]->GetIsDrawPile()){
      throw "Not a drawpile";
    }
    if (drawPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
          throw "DeckParts too big";
        }
    }
    this->drawPiles = drawPileVector;
}

void EnemyRoom::SetDiscardPiles (std::vector<std::shared_ptr<DeckParts>> discardPileVector){
  for(int i = 0; i < int(discardPileVector.size()); i++){
    if (!discardPileVector[i]->GetIsDiscardPile()){
       throw "Not a discard pile";
     }
    if (discardPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
          throw "DeckParts too big";
        }
    }

    this->discardPiles = discardPileVector;

}

void EnemyRoom::SetHands (std::vector<std::shared_ptr<DeckParts>> handVector){
  for ( int i = 0; i< int(handVector.size()); i++){
    if (!handVector[i]->GetIsHand()){
      throw "Not a hand";
    }
    if (handVector[i]->GetSize() > this->hands[i]->GetSizeMax()){
          throw "DeckParts too big";
        }
    }
    this->hands = handVector;
}
