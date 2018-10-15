#include "Map.h"

using namespace state;

std::vector<std::shared_ptr<Floor>> Map::GetFloors(){
  return floors;
}

int Map::GetCurrentFloor(){
  return currentFloor;
}

int Map::GetCurrentRoom (){
  return currentRoom;
}

void Map::SetCurrentFloor (int newFloor){
  this->currentFloor = newFloor;
}

void Map::SetCurrentRoom (int newRoom){
  this->currentRoom = newRoom;
}
