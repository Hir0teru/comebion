#include "DeckParts.h"

using namespace state;

DeckParts::DeckParts(){

}
DeckParts::DeckParts(std::shared_ptr<Player> player, bool isHand, bool isDiscardPile, bool isDrawPile){
  this -> isHand = isHand;
  this -> isDiscardPile = isDiscardPile;
  this -> isDrawPile = isDrawPile;
  if (isDrawPile) {
    cards = player->GetDeck()->GetCards();
    size = player->GetDeck()->GetSize();

  }
  else{
    size = 0;
  }
  playerId = player->GetId();
  // int size;
}

DeckParts::~DeckParts(){}

int DeckParts::GetPlayerId (){
  return playerId;
}

bool DeckParts::GetIsDiscardPile (){
  return isDiscardPile;
}

bool DeckParts::GetIsDrawPile (){
  return isDrawPile;
}

bool DeckParts::GetIsHand (){
  return isHand;
}

std::vector<std::shared_ptr<Card>> DeckParts::GetCards (){
  return cards;
}

void DeckParts::SetCards (std::vector<std::shared_ptr<Card>> newCards){
  this->cards = newCards;
}

int DeckParts::GetSize (){
  return size;
}

void DeckParts::SetSize (int newSize){
  this->size = newSize;
}
