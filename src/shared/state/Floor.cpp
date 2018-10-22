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
      enemies.push_back(std::make_shared<Enemy>());
      room = new EnemyRoom(element, enemies);
      this->firstRoom.reset(room);
      this->currentRoom.reset(room);

      for (int i = 1; i<9; i++){
        randomNumber = rand() % 100;
        if (randomNumber < 60){
          std::cout<<"enemy"<<std::endl;
          std::vector<std::shared_ptr<Enemy>> enemies;
          std::cout<<"enemy2"<<std::endl;
          std::shared_ptr<Enemy> test = std::make_shared<Enemy>();
          std::cout<<"lolilol"<<std::endl;
          enemies.push_back(std::make_shared<Enemy>());
          std::cout<<"enemy3"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<EnemyRoom>(element, enemies));
        } else if (randomNumber < 80){
          std::cout<<"sleep"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<SleepRoom>(element, randomNumber-60));
        } else {
          std::cout<<"str"<<std::endl;
          std::vector<std::shared_ptr<Card>> reward;
          reward.push_back(std::make_shared<Card>("reward1", 0));
          reward.push_back(std::make_shared<Card>("reward2", 0));
          reward.push_back(std::make_shared<Card>("reward3", 0));
          currentRoom->SetNextRoom(std::make_shared<SpecialTrainingRoom>(element, reward));
        }
        std::cout << currentRoom << " --- " << currentRoom->GetNextRoom() << std::endl;
        std::cout << currentRoom->GetNextRoom() << std::endl;
        std::cout << "bug" << std::endl;
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
