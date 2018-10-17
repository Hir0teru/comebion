#include "GameState.h"

using namespace state;

GameState::~GameState()
{

}

std::vector<std::shared_ptr<Player>> GameState::GetPlayers(){
  return players;
}

std::shared_ptr<Map> GameState::GetMap(){
  return map;
}

std::shared_ptr<Rules> GameState::GetRules(){
  return rules;
}

bool GameState::GetIsInsideRoom (){
  return isInsideRoom;
}

void GameState::SetIsInsideRoom (bool newIsInsideRoom){
  this->isInsideRoom = newIsInsideRoom;
}
