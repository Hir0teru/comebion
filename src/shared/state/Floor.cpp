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
  SkillManager* SM = SkillManager::instance();
  std::vector<EnemySkill*> skills;
  skills.push_back((*SM)[0]);
  skills.push_back((*SM)[1]);
  skills.push_back((*SM)[2]);
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
      std::vector<std::unique_ptr<Enemy>> enemies;
      std::unique_ptr<Enemy> enemy= std::make_unique<Enemy>("Enemy", element, "image",
        0, 0, 80, 2, skills, 80);
      enemy -> SetElement(element);
      if (element == 1){
        enemy -> SetImage("res/textures/Enemy/Air/30.png");
        }
      else{
        if (element == 2){
          enemy -> SetImage("res/textures/Enemy/Water/14.png");
        }
        else{
          if (element == 3){
            enemy -> SetImage("res/textures/Enemy/Earth/22.png");
          }
          else{
            enemy -> SetImage("res/textures/Enemy/Fire/8.png");
          }
        }
      }
      enemies.push_back(std::move(enemy));
      std::shared_ptr<Room> room = std::make_shared<EnemyRoom>(element, std::move(enemies));
      this->firstRoom = room;
      this->currentRoom = room;

      for (int i = 1; i<9; i++){
        randomNumber = rand() % 100;
        if (randomNumber < 60){
          std::cout<<"room "<<i<<": enemyRoom"<<std::endl;
          enemies.clear();

          std::unique_ptr<Enemy> enemy2= std::make_unique<Enemy>("Enemy", element, "image",
            0, 0, 80, 2, skills, 80);
          enemy2 -> SetElement(element);
          if (element == 1){
            enemy2 -> SetImage("res/textures/Enemy/Air/30.png");
          }
          else{
            if (element == 2){
              enemy2 -> SetImage("res/textures/Enemy/Water/14.png");
            }
            else{
              if (element == 3){
                enemy2 -> SetImage("res/textures/Enemy/Earth/22.png");
              }
              else{
                enemy2 -> SetImage("res/textures/Enemy/Fire/8.png");
              }
            }
          }


          enemies.push_back(std::move(enemy2));
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          currentRoom->SetNextRoom(ER);
        } else if (randomNumber < 80){
          std::cout<<"room "<<i<<": sleepRoom"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<SleepRoom>(element, randomNumber-50));
          std::cout << currentRoom -> GetNextRoom() -> GetHeal() << std::endl;
        } else {
          std::cout<<"room "<<i<<": specialTrainingRoom"<<std::endl;
          std::vector<Card*> reward;
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          reward.push_back((*CM)[0]);
          currentRoom->SetNextRoom(std::make_shared<SpecialTrainingRoom>(element, reward));
        }
        currentRoom = currentRoom -> GetNextRoom();
        // room = nullptr;
      }
      // final room
      enemies.clear();

      std::unique_ptr<Enemy> enemy2= std::make_unique<Enemy>();
      enemy2 -> SetElement(element);
      if (element == 1){
        enemy2 -> SetImage("res/textures/Enemy/Air/bison.png");
        enemy2 -> SetName("Flying Bison");
        enemy2 -> SetMaxLife(300);
        enemy2 -> SetLife(300);
        enemies.push_back(std::move(enemy2));

        std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
        ER -> SetImageMapRoom("res/textures/Map/air_bison.png");
        std::cout << "final room" << std::endl;
        currentRoom->SetNextRoom(ER);
      }
      else{
        if (element == 2){
          enemy2 -> SetImage("res/textures/Enemy/Water/La.png");
          enemy2 -> SetName("La");
          enemy2 -> SetMaxLife(500);
          enemy2 -> SetLife(500);
          enemies.push_back(std::move(enemy2));

          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          ER -> SetImageMapRoom("res/textures/Map/water.png");
          std::cout << "final room" << std::endl;
          currentRoom->SetNextRoom(ER);
        }
        else{
          if (element == 3){
            enemy2 -> SetImage("res/textures/Enemy/Earth/badgermole.png");
            enemy2 -> SetName("Badgermole");
            enemy2 -> SetMaxLife(300);
            enemy2 -> SetLife(300);
            enemies.push_back(std::move(enemy2));

            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER -> SetImageMapRoom("res/textures/Map/badgermole.png");
            std::cout << "final room" << std::endl;
            currentRoom->SetNextRoom(ER);
          }
          else{
            enemy2 -> SetImage("res/textures/Enemy/Fire/blue_dragon.png");
            enemy2 -> SetName("Blue Dragon");
            enemy2 -> SetMaxLife(250);
            enemy2 -> SetLife(250);
            enemies.push_back(std::move(enemy2));
            std::unique_ptr<Enemy> enemy3= std::make_unique<Enemy>();
            enemy3 -> SetElement(element);
            enemy3 -> SetImage("res/textures/Enemy/Fire/red_dragon.png");
            enemy3 -> SetName("Red Dragon");
            enemy3 -> SetMaxLife(250);
            enemy3 -> SetLife(250);
            enemies.push_back(std::move(enemy3));

            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER -> SetImageMapRoom("res/textures/Map/dragon.png");
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
  this -> currentRoom = currentRoom;
}
