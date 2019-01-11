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
  int enemyStrenght = 0;
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
      std::unique_ptr<Enemy> enemy11= std::make_unique<Enemy>(element, 2);
      enemy11->SetId(3);
      enemies.push_back(std::move(enemy11));
      std::unique_ptr<Enemy> enemy111= std::make_unique<Enemy>(element, 2);
      enemy111->SetId(4);
      enemies.push_back(std::move(enemy111));
      // if(rand()%100 > 40){
      //   std::unique_ptr<Enemy> enemy1= std::make_unique<Enemy>(element, 2);
      //   enemy1->SetId(3);
      //   enemies.push_back(std::move(enemy1));
      // }
      std::shared_ptr<Room> room = std::make_shared<EnemyRoom>(element, std::move(enemies));
      this->firstRoom = room;
      this->currentRoom = room;
      enemyStrenght++;

      for (int i = 1; i<9; i++){
        randomNumber = rand() % 100;
        if (randomNumber < 60){
          std::cout<<"room "<<i<<": enemyRoom"<<std::endl;
          enemies.clear();
          std::unique_ptr<Enemy> enemy2= std::make_unique<Enemy>(element, 3);
          enemy2->SetId(2);
          enemy2->SetStatAttack(enemyStrenght);
          enemy2->SetStatBlock(enemyStrenght);
          enemies.push_back(std::move(enemy2));
          if(rand()%100 > 30){
            std::unique_ptr<Enemy> enemy3= std::make_unique<Enemy>(element, 2);
            enemy3->SetId(3);
            enemy3->SetStatAttack(enemyStrenght);
            enemy3->SetStatBlock(enemyStrenght);
            enemies.push_back(std::move(enemy3));
            if(rand()%100 > 50){
              std::unique_ptr<Enemy> enemy4= std::make_unique<Enemy>(element, 2);
              enemy4->SetId(4);
              enemy4->SetStatAttack(enemyStrenght);
              enemy4->SetStatBlock(enemyStrenght);
              enemies.push_back(std::move(enemy4));
            }
          }
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          currentRoom->SetNextRoom(ER);
          enemyStrenght++;
        } else if (randomNumber < 80){
          std::cout<<"room "<<i<<": sleepRoom"<<std::endl;
          currentRoom->SetNextRoom(std::make_shared<SleepRoom>(element, randomNumber-50));
          enemyStrenght++;
          //std::cout << currentRoom->GetNextRoom()->GetHeal() << std::endl;
        } else {
          std::cout<<"room "<<i<<": specialTrainingRoom"<<std::endl;
          std::vector<Card*> reward;
          int card;
          for (int i = 0; i<3; i++){
            card = rand() % 24 + 2;
            reward.push_back((*CM)[card]);
          }
          currentRoom->SetNextRoom(std::make_shared<SpecialTrainingRoom>(element, reward));
          enemyStrenght++;
        }
        currentRoom = currentRoom->GetNextRoom();
        // room = nullptr;
      }
      // final room
      enemies.clear();

      std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>(element, 0);
      enemy2->SetId(2);
      enemy2->SetStatAttack(enemyStrenght);
      enemy2->SetStatBlock(enemyStrenght);
      enemies.push_back(std::move(enemy2));
      if (element == 1){
        std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
        ER->SetImageMapRoom("res/textures/Map/air_bison.png");
        std::cout << "final room" << std::endl;
        currentRoom->SetNextRoom(ER);
        enemyStrenght++;
      }
      else{
        if (element == 2){
          std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
          ER->SetImageMapRoom("res/textures/Map/water.png");
          std::cout << "final room" << std::endl;
          currentRoom->SetNextRoom(ER);
          enemyStrenght++;
        }
        else{
          if (element == 3){
            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER->SetImageMapRoom("res/textures/Map/badgermole.png");
            std::cout << "final room" << std::endl;
            currentRoom->SetNextRoom(ER);
            enemyStrenght++;
          }
          else{
            std::unique_ptr<Enemy> enemy3= std::make_unique<Enemy>(element, -1);
            enemy3->SetId(3);
            enemy3->SetStatAttack(enemyStrenght);
            enemy3->SetStatBlock(enemyStrenght);
            enemies.push_back(std::move(enemy3));

            std::shared_ptr<EnemyRoom> ER = std::make_shared<EnemyRoom>(element, std::move(enemies));
            ER->SetImageMapRoom("res/textures/Map/dragon.png");
            std::cout << "final room" << std::endl;
            currentRoom->SetNextRoom(ER);
            enemyStrenght++;
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
