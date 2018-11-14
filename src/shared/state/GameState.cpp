#include "GameState.h"
#include "PlayerManager.h"

using namespace state;

// constructor for test
GameState::GameState (){
  map = std::move(std::make_unique<Map>());
  std::vector<std::unique_ptr<InfoPlayer>> infoPlayers;
  infoPlayers.push_back(std::move(std::make_unique<InfoPlayer>()));
  rules = std::move(std::make_unique<Rules>(1, std::move(infoPlayers)));
  isInsideRoom = false;
  isGameLost = false;
}

GameState::~GameState(){}

Map* GameState::GetMap(){
  return map.get();
}

Rules* GameState::GetRules(){
  return rules.get();
}

bool GameState::GetIsInsideRoom (){
  return isInsideRoom;
}

void GameState::SetIsInsideRoom (bool newIsInsideRoom){
  this->isInsideRoom = newIsInsideRoom;
}

std::vector<Player*>& GameState::GetPlayers(){
  return players;
}

void GameState::SetPlayers(std::vector<Player*>& players){
  this -> players = players;
}

bool GameState::GetIsGameLost(){
  return isGameLost;
}

void GameState::SetIsGameLost(bool isGameLost){
  this -> isGameLost = isGameLost;
}
