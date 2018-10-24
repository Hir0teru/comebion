#include "Map.h"
#include <iostream>

using namespace state;

Map::Map(){
  std::cout<<"creation floor 1"<<std::endl;
  floors.push_back(std::move(std::make_unique<Floor>(0, 1))); //floor number, floor element
  std::cout<<"creation floor 2"<<std::endl;
  floors.push_back(std::move(std::make_unique<Floor>(1, 2)));
  std::cout<<"creation floor 3"<<std::endl;
  floors.push_back(std::move(std::make_unique<Floor>(2, 3)));
  std::cout<<"creation floor 4"<<std::endl;
  floors.push_back(std::move(std::make_unique<Floor>(3, 4)));
  currentFloor = 0;
}

Map::~Map()
{

}

std::vector<Floor*> Map::GetFloors(){
  std::vector<Floor*> vectorFloor;
  vectorFloor.push_back(this->floors[0].get());
  if (floors.size() == 2){
    vectorFloor.push_back(this->floors[1].get());
  }
  return vectorFloor;
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
