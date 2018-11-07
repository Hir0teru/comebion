#include "CardManager.h"
#include "SkillManager.h"
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
      this->floorNumber = floorNumber;
      this->element = element;
      int randomNumber;
      std::vector<std::unique_ptr<Enemy>> enemies;
      std::unique_ptr<Enemy> enemy= std::make_unique<Enemy>(element, 2);
      enemy->SetId(2);
      enemies.push_back(std::move(enemy));
      std::shared_ptr<Room> room = std::make_shared<EnemyRoom>(element, std::move(enemies));
      this->firstRoom = room;
      this->currentRoom = room;

      for (int i = 1; i<9; i++){
        randomNumber = rand() % 100;
        if (randomNumber < 60){
          std::cout<<"room "<<i<<": enemyRoom"<<std::endl;
          enemies.clear();
          std::unique_ptr<Enemy> enemy2= std::make_unique<Enemy>(element, 3);
          enemy2->SetId(2);
          enemies.push_back(std::move(enemy2));
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          currentRoom->SetNextRoom(ER);
        } else if (randomNumber < 80){
          std::cout<<"room "<<i<<": sleepRoom"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<SleepRoom>(element, randomNumber-50));
          std::cout << currentRoom->GetNextRoom()->GetHeal() << std::endl;
        } else {
          std::cout<<"room "<<i<<": specialTrainingRoom"<<std::endl;
          std::vector<Card*> reward;
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          currentRoom->SetNextRoom(std::make_shared<SpecialTrainingRoom>(element, reward));
        }
        currentRoom = currentRoom->GetNextRoom();
        // room = nullptr;
      }
      // final room
      enemies.clear();

      std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(element, 0);
      enemy2->SetId(2);
      enemies.push_back(std::move(enemy2));
      if (element == 1){
        std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
        ER->SetImageMapRoom("res/textures/Map/air_bison.png");
        std::cout << "final room" << std::endl;
        currentRoom->SetNextRoom(ER);
      }
      else{
        if (element == 2){
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          ER->SetImageMapRoom("res/textures/Map/water.png");
          std::cout << "final room" << std::endl;
          currentRoom->SetNextRoom(ER);
        }
        else{
          if (element == 3){
            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER->SetImageMapRoom("res/textures/Map/badgermole.png");
            std::cout << "final room" << std::endl;
            currentRoom->SetNextRoom(ER);
          }
          else{
            std::unique_ptr<Enemy> enemy3= std::make_unique<Enemy>(element, -1);
            enemy3->SetId(3);
            enemies.push_back(std::move(enemy3));

            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER->SetImageMapRoom("res/textures/Map/dragon.png");
            std::cout << "final room" << std::endl;
            currentRoom->SetNextRoom(ER);
          }
        }
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

std::shared_ptr<Room>& Floor::GetFirstRoom (){
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

std::shared_ptr<Room>& Floor::GetCurrentRoom(){
  return currentRoom;
}

void Floor::SetCurrentRoom(std::shared_ptr<Room>& currentRoom){
  this->currentRoom = currentRoom;
}
