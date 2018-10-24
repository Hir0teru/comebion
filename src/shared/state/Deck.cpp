#include "CardManager.h"
#include "Deck.h"
#include <iostream>
#include <stdexcept>
using namespace state;



Deck::Deck (){
  size = 0;
  sizeMax = 15;
}

Deck::Deck (int element, int size){
  CardManager* CM = CardManager::instance();

  this -> size = size;
  if (size > 15){
    sizeMax = size + 5;
  }
  else{
    sizeMax = 15;
  }


  for (int i = 0; i < size/2 ; i++){
    cards.push_back((*CM)[0]);
  }
  for (int i = int(size/2); i < size; i++){
    cards.push_back((*CM)[1]);
  }
}

Deck::~Deck(){
  std::cout << "Deck destroyed" << std::endl;
}

std::vector<Card*> Deck::GetCards (){
  return cards;
}

void Deck::SetCards (std::vector<Card*> newCards){
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
    size = sizeMax;
  }
  else{
    size = newSize;
  }
}

int Deck::GetSizeMax (){
  return sizeMax;
}
