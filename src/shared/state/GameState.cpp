#include "GameState.h"

using namespace state;



// constructor for test
GameState::GameState (){
  players.reserve(1);
  players[0].reset (new Player("Aang", 1, "image.jpg", 0, 0, 60, 0, 60));
  map.reset(new Map());
  std::vector<std::shared_ptr<InfoPlayer>> infoPlayers;
  infoPlayers.reserve(1);
  infoPlayers[0].reset(new InfoPlayer);
  rules.reset(new Rules(1, infoPlayers));
  isInsideRoom = false;

}

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
