#include "CardManager.h"
#include "Floor.h"
#include "EnemyRoom.h"
#include "SleepRoom.h"
#include "SpecialTrainingRoom.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

using namespace state;

Floor::~Floor()
{

}

Floor::Floor()
{

}

Floor::Floor (int floorNumber, int element){
  CardManager* CM = CardManager::instance();
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
      std::vector<std::unique_ptr<Enemy>> enemies;
      enemies.push_back(std::move(std::make_unique<Enemy>()));
      room = new EnemyRoom(element, std::move(enemies));
      this->firstRoom.reset(room);
      this->currentRoom.reset(room);

      for (int i = 1; i<9; i++){
        randomNumber = rand() % 100;
        if (randomNumber < 60){
          std::cout<<"room "<<i<<": enemyRoom"<<std::endl;
          enemies.clear();
          enemies.push_back(std::move(std::make_unique<Enemy>()));
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          currentRoom->SetNextRoom(ER);
        } else if (randomNumber < 80){
          std::cout<<"room "<<i<<": sleepRoom"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<SleepRoom>(element, randomNumber-60));
        } else {
          std::cout<<"room "<<i<<": specialTrainingRoom"<<std::endl;
          std::vector<Card*> reward;
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          currentRoom->SetNextRoom(std::make_shared<SpecialTrainingRoom>(element, reward));
        }
        // room = nullptr;
      }
      this->currentRoom = this->firstRoom;
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

int Floor::GetFloorNumber (){
  return floorNumber;
}

void Floor::SetFloorNumber (int newFloorNumber){
  if (newFloorNumber >= 0 && newFloorNumber <=3) {
    this->floorNumber = newFloorNumber;
  }
}
