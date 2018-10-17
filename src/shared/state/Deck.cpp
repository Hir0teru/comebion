#include "Deck.h"
#include <iostream>
#include <stdexcept>
using namespace state;



Deck::Deck (){
  size = 0;
  sizeMax = 15;
  cards.reserve(sizeMax);
}

Deck::Deck (int element, int size){
  this -> size = size;
  if (size > 15){
    sizeMax = size + 5;
  }
  else{
    sizeMax = 15;
  }
  cards.reserve(sizeMax);
  Buff* buff = new Buff();
  Debuff* debuff = new Debuff();
  for (int i = 0; i < size/2 ; i++){
    cards[i].reset( new Card("basic attack", 1, 1, "None", element, 6, 0, 0, 0, 0, *debuff, *buff ));
  }
  for (int i = int(size/2); i < size; i++){
    cards[i].reset (new Card("basic defense", 1, 0, "None", element, 5, 0, 0, 0, 0, *debuff, *buff));
  }

  delete(buff);
  delete(buff);
}

Deck::~Deck(){
  std::cout << "Deck destroyed" << std::endl;
}

std::vector<std::shared_ptr<Card>> Deck::GetCards (){
  return cards;
}

void Deck::SetCards (std::vector<std::shared_ptr<Card>> newCards){
  int newSize = newCards.size();
  if (newSize > sizeMax){
    throw std::invalid_argument( "Errror : adding too much cards. Not changing");
  }
  else{
    this -> cards = newCards;
    this -> size = newSize;
  }
}

int Deck::GetSize(){
  return size;
}

void Deck::SetSize (int newSize){
  if (newSize > sizeMax){
    std::cout << "error with size " << newSize << std::endl;
    size = sizeMax;
  }
  else{
    size = newSize;
  }
}

int Deck::GetSizeMax (){
  return sizeMax;
}
