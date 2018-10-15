#include "Floor.h"

using namespace state;

std::string Floor::GetElement (){
  return element;
}

std::string Floor::GetFloorImage (){
  return floorImage;
}

std::vector<std::shared_ptr<Room>> Floor::GetRooms (){
  return rooms;
}

void Floor::SetRooms (std::vector<std::shared_ptr<Room>> newRooms){
  this->rooms = newRooms;
}
