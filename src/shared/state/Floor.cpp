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

Floor::Floor (int floorNumber, int element){
  if (floorNumber < 0 || floorNumber > 3){
    throw std::out_of_range("Not a valid floor number. Value must be between 0 and 3");
  }
  else{
    if (element < 0 || element > 4){
      throw std::out_of_range("Not a valid element. Value must be between 0 and 4.");
    }
    else{
      this -> floorNumber = floorNumber;
      this -> element = element;
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
