#include "Rules.h"

using namespace state;

Rules::Rules():isGameLost(false), isGameOver(false), nbPlayers(1){
  initPlayer.reserve(1);
}

Rules::Rules(int nbPlayers, std::vector<std::shared_ptr<InitPlayer>> initPlayer):isGameLost(false), isGameOver(false), nbPlayers(nbPlayers), initPlayer(initPlayer)
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

// std::vector<std::shared_ptr<InitPlayer>> Rules::GetInitPlayer (){
//   return initPlayer;
// }
//
// void Rules::SetInitPlayer (std::vector<std::shared_ptr<InitPlayer>> newInitPlayer){
//   this->initPlayer = newInitPlayer;
// }
