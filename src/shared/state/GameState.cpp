#include "GameState.h"

using namespace state;

std::vector<std::shared_ptr<Player>> GameState::GetPlayers(){
  return players;
}

std::shared_ptr<Map> GameState::GetMap(){
  return map;
}

std::shared_ptr<Rules> GameState::GetRules(){
  return rules;
}
