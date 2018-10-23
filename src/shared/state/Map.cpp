#include "Map.h"
#include <iostream>

using namespace state;

Map::Map(){
  floors.push_back(std::make_shared<Floor>(0, 1)); //floor number, floor element
  std::cout << "Bug3" << std::endl;

  floors.push_back(std::make_shared<Floor>(1, 2));
  floors.push_back(std::make_shared<Floor>(2, 3));
  floors.push_back(std::make_shared<Floor>(3, 4));
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
