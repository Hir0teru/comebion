#include "Floor.h"

using namespace state;

Floor::~Floor()
{

}

std::string Floor::GetElement (){
  return element;
}

std::string Floor::GetFloorImage (){
  return floorImage;
}

std::vector<std::shared_ptr<Room>> Floor::GetFirstRoom (){
  return firstRoom;
}

void Floor::SetFirstRoom (std::shared_ptr<Room> newFirstRoom){
  this->rooms = newFirstRoom;
}
