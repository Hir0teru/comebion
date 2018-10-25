#include "PlayerManager.h"
#include <iostream>
#include <memory>

using namespace state;

PlayerManager* PlayerManager::inst;

PlayerManager::PlayerManager (int nbPlayers){
  players.push_back(std::move(std::make_unique<Player>("Aang", 1, "image.jpg", 0, 0, 60, 0, 60)));
  if (nbPlayers > 1){
    players.push_back(std::move(std::make_unique<Player>("Korra", 2, "image.jpg", 0, 0, 60, 0, 60)));
  }
  this->nbPlayers = nbPlayers;
}

PlayerManager* PlayerManager::instance (){
  if (!inst){
    inst = new PlayerManager(1);
  }
  return inst;
}

Player* PlayerManager::operator[] (int i){
  return players[i].get();
}

int PlayerManager::GetNbPlayers(){
  return nbPlayers;
}
