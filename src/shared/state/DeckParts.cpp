#include "DeckParts.h"

using namespace state;

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
