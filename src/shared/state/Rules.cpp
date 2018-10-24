#include "Rules.h"

using namespace state;

Rules::Rules():isGameLost(false), isGameOver(false), nbPlayers(1){
  infoPlayer.reserve(1);
}

Rules::~Rules()
{

}

Rules::Rules(int nbPlayers, std::vector<std::unique_ptr<InfoPlayer>> newInfoPlayer):isGameLost(false), isGameOver(false)
{
  // Only 1 or 2 player(s)
  if (nbPlayers < 1) {
    this->nbPlayers = 1;
  } else if (nbPlayers > 2) {
    this->nbPlayers = 2;
  } else {
    this->nbPlayers = nbPlayers;
  }

  this->infoPlayer = std::move(newInfoPlayer);
  if ((int) infoPlayer.size() < this->nbPlayers ){
    throw std::out_of_range("Not enough rules for the number of players");
  }

  this->infoPlayer = std::move(newInfoPlayer);
}

bool Rules::GetIsGameLost (){
  return isGameLost;
}

bool Rules::GetIsGameOver (){
  return isGameOver;
}

void Rules::SetIsGameLost (bool newIsGameLost){
  if (newIsGameLost){
    this->isGameOver = true;
  }
  this->isGameLost = newIsGameLost;
}

void Rules::SetIsGameOver (bool newIsGameOver){
  this->isGameOver = newIsGameOver;
}

int Rules::GetNbPlayers (){
  return nbPlayers;
}

void Rules::SetNbPlayers (int newNbPlayers){
  if (newNbPlayers < 1) {
    this->nbPlayers = 1;
  } else if (newNbPlayers > 2) {
    this->nbPlayers = 2;
  } else{
    this->nbPlayers = newNbPlayers;
  }
}

std::vector<InfoPlayer*> Rules::GetInfoPlayer (){
  std::vector<InfoPlayer*> vectorInfoPlayer;
  vectorInfoPlayer.push_back(this->infoPlayer[0].get());
  if (infoPlayer.size() == 2){
    vectorInfoPlayer.push_back(this->infoPlayer[1].get());
  }
  return vectorInfoPlayer;
}

void Rules::SetInfoPlayer (std::vector<std::unique_ptr<InfoPlayer>> newInfoPlayer){
  this->infoPlayer = std::move(newInfoPlayer);
}
