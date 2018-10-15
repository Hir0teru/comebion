#include "Rules.h"

using namespace state;

bool Rules::GetIsGameLost (){
  return isGameLost;
}

bool Rules::GetIsGameOver (){
  return isGameOver;
}

void Rules::SetIsGameLost (bool lost){
  this->isGameLost = lost;
}

void Rules::SetIsGameOver (bool over){
  this->isGameOver = over;
}

int Rules::GetNbPlayers (){
  return nbPlayers;
}

void Rules::SetNbPlayers (int newNbPlayers){
  this->nbPlayers = newNbPlayers;
}

std::vector<std::shared_ptr<InitPlayer>> Rules::GetInitPlayer (){
  return initPlayer;
}

void Rules::SetInitPlayer (std::vector<std::shared_ptr<InitPlayer>> newInitPlayer){
  this->initPlayer = newInitPlayer;
}