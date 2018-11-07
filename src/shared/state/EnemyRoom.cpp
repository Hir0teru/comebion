#include "EnemyRoom.h"
#include "PlayerManager.h"
#include <iostream>
using namespace state;

EnemyRoom::~EnemyRoom(){}

EnemyRoom::EnemyRoom (int element, std::vector<std::unique_ptr<Enemy>> enemies): Room(element, false, true, false), turn(0), entityTurn(0), isGameLost(false)
{
  PlayerManager* PM = PlayerManager::instance();
  if (enemies.size() <= 0) {
    throw std::out_of_range("not enough enemies");
  } else if (enemies.size() > 3) {
    std::cout<<"too many enemies "<< enemies.size()<<std::endl;
    throw std::out_of_range("too many enemies");
  } else {
    this->enemies = std::move(enemies);
  }

  hands.push_back(std::move(std::make_unique<DeckParts>((*PM)[0], true, false, false)));
  discardPiles.push_back(std::move(std::make_unique<DeckParts>((*PM)[0], false, true, false)));
  drawPiles.push_back(std::move(std::make_unique<DeckParts>((*PM)[0], false, false, true)));

  if (PM->GetNbPlayers() > 1){
    hands.push_back(std::move(std::make_unique<DeckParts>((*PM)[1], true, false, false)));
    discardPiles.push_back(std::move(std::make_unique<DeckParts>((*PM)[1], false, true, false)));
    drawPiles.push_back(std::move(std::make_unique<DeckParts>((*PM)[1], false, false, true)));
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

std::vector<DeckParts*> EnemyRoom::GetDrawPiles (){
  std::vector<DeckParts*> vectorDrawPiles;
  vectorDrawPiles.push_back(this->drawPiles[0].get());
  if (drawPiles.size() == 2){
    vectorDrawPiles.push_back(this->drawPiles[1].get());
  }
  return vectorDrawPiles;
}

std::vector<DeckParts*> EnemyRoom::GetDiscardPiles (){
  std::vector<DeckParts*> vectorDiscardPiles;
  vectorDiscardPiles.push_back(this->discardPiles[0].get());
  if (discardPiles.size() == 2){
    vectorDiscardPiles.push_back(this->discardPiles[1].get());
  }
  return vectorDiscardPiles;
}

std::vector<DeckParts*> EnemyRoom::GetHands (){
  std::vector<DeckParts*> vectorHands;
  vectorHands.push_back(this->hands[0].get());
  if (hands.size() == 2){
    vectorHands.push_back(this->hands[1].get());
  }
  return vectorHands;
}

void EnemyRoom::SetDrawPiles (std::vector<std::unique_ptr<DeckParts>> drawPileVector){
  for(int i = 0; i < int( drawPileVector.size()); i++){
    if (!drawPileVector[i]->GetIsDrawPile()){
      std::cout<<"Not a drawpile"<<std::endl;
      throw "Not a drawpile";
    }
    if (drawPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
      std::cout<<"DeckParts too big"<<std::endl;
          throw "DeckParts too big";
        }
    }
    this->drawPiles = std::move(drawPileVector);
}

void EnemyRoom::SetDiscardPiles (std::vector<std::unique_ptr<DeckParts>> discardPileVector){
  for(int i = 0; i < int(discardPileVector.size()); i++){
    if (!discardPileVector[i]->GetIsDiscardPile()){
      std::cout<<"Not a discardPile"<<std::endl;
      throw "Not a discard pile";
    }
    if (discardPileVector[i]->GetSize() > this->drawPiles[i]->GetSizeMax()){
      std::cout<<"DeckParts too big"<<std::endl;
      throw "DeckParts too big";
    }
  }
    this->discardPiles = std::move(discardPileVector);
}

void EnemyRoom::SetHands (std::vector<std::unique_ptr<DeckParts>> handVector){
  for ( int i = 0; i< int(handVector.size()); i++){
    if (!handVector[i]->GetIsHand()){
      std::cout<<"Not a hand"<<std::endl;
      throw "Not a hand";
    }
    if (handVector[i]->GetSize() > this->hands[i]->GetSizeMax()){
      std::cout<<"DeckParts too big"<<std::endl;
      throw "DeckParts too big";
    }
  }
    this->hands = std::move(handVector);
}


std::vector<std::unique_ptr<Enemy>>& EnemyRoom::GetEnemies(){
  return enemies;
}


void EnemyRoom::SetTurn(int turn){
  this -> turn = turn;
}

void EnemyRoom::SetEntityTurn(int entityNb){
  this -> entityTurn = entityNb;
}

bool EnemyRoom::GetIsFightWon(){
  return isFightWon;
}

void EnemyRoom::SetIsFightWon(bool isFightWon){
  this->isFightWon = isFightWon;
}

std::vector<Card*> EnemyRoom::GetReward(){
  return reward;
}

void EnemyRoom::SetReward(std::vector<Card*> reward){
  this -> reward = reward;
}
