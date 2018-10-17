#include "Deck.h"

using namespace state;



Deck::Deck (){}
Deck::Deck (std::string element, int size){
  cards.reserve(15);
  for (int i = 0; i < 5 ; i++){
    cards[i].reset( new Card("basic attack", element));
  }
  for (int i = 5; i < 10; i++){
    cards[i].reset (new Card("basic defense", element));
  }
  this -> size = size;
  sizeMax = 15;
}

Deck::~Deck(){}

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
