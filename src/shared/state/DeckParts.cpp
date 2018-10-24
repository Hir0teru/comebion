#include "DeckParts.h"
#include <iostream>
#include<stdexcept>

using namespace state;

DeckParts::DeckParts(){

}
DeckParts::DeckParts(std::shared_ptr<Player> player, bool isHand, bool isDiscardPile, bool isDrawPile){
  if(!((isHand && !isDiscardPile && !isDrawPile) || (!isHand && isDiscardPile && !isDrawPile) ||
  (!isHand && !isDiscardPile && isDrawPile))){
    throw std::out_of_range("Can only be a hand OR a discardPile OR a drawPile");
  }
  else{
    this -> isHand = isHand;
    this -> isDiscardPile = isDiscardPile;
    this -> isDrawPile = isDrawPile;
    if (isDrawPile) {
      sizeMax = player->GetDeck()->GetSizeMax() + 10;
      cards.reserve(sizeMax);
      cards = player->GetDeck()->GetCards();
      size = player->GetDeck()->GetSize();
    }
    else{
      if (isDiscardPile){
        sizeMax = player->GetDeck()->GetSizeMax() + 10;
        cards.reserve(sizeMax);
        size = 0;
      }
      else{
        cards.reserve(7);
        size = 0;
        sizeMax = 7;
      }
    }
    playerId = player->GetId();
  // int size;
  }
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
  int newsize = newCards.size();
  if (newsize > sizeMax){
    throw std::invalid_argument("Error : too much cards to add");
  }
  else{
    this -> cards = newCards;
    this -> size = newsize;
  }
}

int DeckParts::GetSize (){
  return size;
}

void DeckParts::SetSize (int newSize){
  if (newSize > sizeMax){
    this -> size = this -> sizeMax;
  }
  else{
    this->size = newSize;
  }
}

int DeckParts::GetSizeMax (){
  return sizeMax;
}

void DeckParts::SetSizeMax (int newSizeMax){
  if (newSizeMax < size){
    std::cout<<"Too much elements in deckPart to change sizeMax now"<<std::endl;
    throw "Too much elements in deckPart to change sizeMax now";
  }
  else{
    this->sizeMax = newSizeMax;
  }
}
