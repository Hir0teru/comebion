#include "GameState.h"

using namespace state;



// constructor for test
GameState::GameState (){

  players.push_back(std::move(std::make_unique<Player>("Aang", 1, "image.jpg", 0, 0, 60, 0, 60)));
  map = std::move(std::make_unique<Map>());
  std::vector<std::unique_ptr<InfoPlayer>> infoPlayers;
  infoPlayers.push_back(std::move(std::make_unique<InfoPlayer>()));
  rules = std::move(std::make_unique<Rules>(1, std::move(infoPlayers)));
  isInsideRoom = false;

}

GameState::~GameState()
{

}

std::vector<Player*> GameState::GetPlayers(){
  std::vector<Player*> vectorPlayer;
  vectorPlayer.push_back(this->players[0].get());
  if (players.size() == 2){
    vectorPlayer.push_back(this->players[1].get());
  }
  return vectorPlayer;
}

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
