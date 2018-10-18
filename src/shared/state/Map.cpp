#include "Map.h"

using namespace state;

Map::Map(){
  floors.reserve(4);
  floors[0].reset(new Floor(0, 1)); //floor number, floor element
  floors[1].reset(new Floor(1, 2));
  floors[2].reset(new Floor(2, 3));
  floors[3].reset(new Floor(3, 4));
  currentFloor = 0;
}

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
  if (newFloor<0 || newFloor > 3){
    throw std::out_of_range("Not a valid value for floor");
  }
  this->currentFloor = newFloor;
}
