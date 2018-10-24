#include "CardManager.h"
#include <iostream>
#include <memory>

using namespace state;

CardManager* CardManager::inst;

CardManager::CardManager (){
}

CardManager* CardManager::instance (){
  if (!inst){
    inst = new CardManager();
  }
  return inst;
}

Card* CardManager::operator[] (int i){
  return cards[i].get();
}
