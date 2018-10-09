#include "Deck.h"

using namespace state;

int Deck::GetSize(){
  return size;
}

void Deck::SetSize (int new_size){
  size = new_size;
}

int Deck::GetSizeMax (){
  return sizeMax;
}
