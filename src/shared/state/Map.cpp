#include "Map.h"

using namespace state;

Map::Map(){}

Map::~Map()
{

}

std::vector<std::shared_ptr<Floor>> Map::GetFloors(){
  return floors;
}

int Map::GetCurrentFloor(){
  return currentFloor;
}

void Map::SetCurrentFloor (int newFloor){
  this->currentFloor = newFloor;
}
