#include "Deck.h"

using namespace state;

std::vector<std::shared_ptr<Card>> Deck::GetCards (){
  return cards;
}

void Deck::SetCards (std::vector<std::shared_ptr<Card>> newCards){
  this->cards = newCards;
}

int Deck::GetSize(){
  return size;
}

void Deck::SetSize (int newSize){
  size = newSize;
}

int Deck::GetSizeMax (){
  return sizeMax;
}
