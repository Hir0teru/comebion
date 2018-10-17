#include "Floor.h"
#include "EnemyRoom.h"
#include "SleepRoom.h"
#include "SpecialTrainingRoom.h"
#include <cstdlib>

using namespace state;

Floor::~Floor()
{

}

Floor::Floor()
{

}

Floor::Floor (int floorNumber, int element): floorNumber(floorNumber), element(element){
  int randomNumber;
  Room* previousRoom;
  Room* room = new EnemyRoom();
  this->firstRoom.reset(room);
  this->currentRoom.reset(room);
  for (int i = 1; i<9; i++){
    randomNumber = rand() % 100;
    if (randomNumber < 60){
      Room* room = new EnemyRoom(element, );
    } else if (randomNumber < 80){
      Room* room = new SleepRoom(element, randomNumber-60);
    } else {
      std::vector<std::shared_ptr<Card>> reward;
      reward.push_back(new Card('reward1', 0));
      reward.push_back(new Card('reward2', 0));
      reward.push_back(new Card('reward3', 0));
      Room* room = new SpecialTrainingRoom(element, reward)
    }
    currentRoom->nextRoom.reset(room);
    currentroom.reset(room);
  }
}


int Floor::GetElement (){
  return element;
}

std::string Floor::GetFloorImage (){
  return floorImage;
}

std::shared_ptr<Room> Floor::GetFirstRoom (){
  return firstRoom;
}

void Floor::SetFirstRoom (std::shared_ptr<Room> newFirstRoom){
  this->firstRoom = newFirstRoom;
}
