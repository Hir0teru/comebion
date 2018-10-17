#include "Rules.h"

using namespace state;

Rules::Rules():isGameLost(false), isGameOver(false), nbPlayers(1){
  infoPlayer.reserve(1);
}

Rules::Rules(int nbPlayers, std::vector<std::shared_ptr<InfoPlayer>> infoPlayer):isGameLost(false), isGameOver(false), nbPlayers(nbPlayers), infoPlayer(infoPlayer)
{

}

bool Rules::GetIsGameLost (){
  return isGameLost;
}

bool Rules::GetIsGameOver (){
  return isGameOver;
}

void Rules::SetIsGameLost (bool newIsGamesLost){
  this->isGameLost = newIsGamesLost;
}

void Rules::SetIsGameOver (bool newIsGameOver){
  this->isGameOver = newIsGameOver;
}

int Rules::GetNbPlayers (){
  return nbPlayers;
}

void Rules::SetNbPlayers (int newNbPlayers){
  this->nbPlayers = newNbPlayers;
}

std::vector<std::shared_ptr<InfoPlayer>> Rules::GetInfoPlayer (){
  return infoPlayer;
}

void Rules::SetInfoPlayer (std::vector<std::shared_ptr<InfoPlayer>> newInfoPlayer){
  this->infoPlayer = newInfoPlayer;
}
