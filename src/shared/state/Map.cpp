#include "Map.h"
#include <iostream>

using namespace state;

Map::Map(){
  std::cout<<"creation floor 1"<<std::endl;
  floors.push_back(std::make_shared<Floor>(0, 1)); //floor number, floor element
  std::cout<<"creation floor 2"<<std::endl;
  floors.push_back(std::make_shared<Floor>(1, 2));
  std::cout<<"creation floor 3"<<std::endl;
  floors.push_back(std::make_shared<Floor>(2, 3));
  std::cout<<"creation floor 4"<<std::endl;
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
