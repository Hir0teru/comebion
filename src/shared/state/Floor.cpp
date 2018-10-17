#include "Floor.h"
#include "EnemyRoom.h"
#include "SleepRoom.h"
#include "SpecialTrainingRoom.h"
#include <cstdlib>
#include <vector>

using namespace state;

Floor::~Floor()
{

}

Floor::Floor()
{

}

Floor::Floor (int floorNumber, int element): floorNumber(floorNumber), element(element){
  int randomNumber;
  Room* room;
  std::vector<std::shared_ptr<Enemy>> enemies;
  enemies.push_back((std::shared_ptr<Enemy>) new Enemy());
  room = new EnemyRoom(element, enemies);
  this->firstRoom.reset(room);
  this->currentRoom.reset(room);
  for (int i = 1; i<9; i++){
    randomNumber = rand() % 100;
    if (randomNumber < 60){
      std::vector<std::shared_ptr<Enemy>> enemies;
      enemies.push_back((std::shared_ptr<Enemy>) new Enemy());
      room = new EnemyRoom(element, enemies);
    } else if (randomNumber < 80){
      room = new SleepRoom(element, randomNumber-60);
    } else {
      std::vector<std::shared_ptr<Card>> reward;
      reward.push_back((std::shared_ptr<Card>) new Card("reward1", 0));
      reward.push_back((std::shared_ptr<Card>) new Card("reward2", 0));
      reward.push_back((std::shared_ptr<Card>) new Card("reward3", 0));
      room = new SpecialTrainingRoom(element, reward);
    }
    currentRoom->SetNextRoom((std::shared_ptr<Room>) room);
    currentRoom.reset(room);
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
