#include "Room.h"
#include <iostream>
using namespace state;

Room::~Room(){}

Room::Room (int elem, bool isSTR, bool isER, bool isSR) {
    entityTurn = 0;
    // Attributes
    if (elem < 0 || elem > 4) {
      element = 0;
    } else {
      element = elem;
    }

    if (isSR) {
      imageMapRoom = "res/textures/Map/sleep.png";
      imageInsideRoom = "res/textures/background/sleep room.png";
    }
    if (isER) {
      if(elem == 1){
        imageMapRoom = "res/textures/Map/air_enemy.png";
        imageInsideRoom = "res/textures/background/air_battle_room.png";
      }
      else{
        if(elem == 2){
          imageMapRoom = "res/textures/Map/water_enemy.png";
          imageInsideRoom = "res/textures/background/water_enemy_room.png";
        }
        else{
          if(elem == 3){
            imageMapRoom = "res/textures/Map/earth_enemy.png";
            imageInsideRoom = "res/textures/background/earth_enemy_room.png";
          }
          else{
            imageMapRoom = "res/textures/Map/fire_enemy.png";
            imageInsideRoom = "res/textures/background/fire_enemy_room.png";

          }
        }
      }
    }
    if (isSTR) {
      imageMapRoom = "res/textures/Map/special_training.png";

      if(elem == 1){
        imageInsideRoom = "res/textures/background/air_battle_room.png";
      }
      else{
        if(elem == 2){
          imageInsideRoom = "res/textures/background/water_enemy_room.png";
        }
        else{
          if(elem == 3){
            imageInsideRoom = "res/textures/background/earth_enemy_room.png";
          }
          else{
            imageInsideRoom = "res/textures/background/fire_enemy_room.png";

          }
        }
      }
    }

    if ((isSTR && !isER && !isSR) || (!isSTR && isER && !isSR) || (!isSTR && !isER && isSR)){
      isSpecialTrainingRoom = isSTR;
      isEnemyRoom = isER;
      isSleepRoom = isSR;
    } else {
      throw std::out_of_range("Room has to be either SpecialTrainingRoom or EnemyRoom or SleepRoom");
    }

    nextRoom = nullptr;
    // Operations
}

std::string Room::GetImageMapRoom (){
  return imageMapRoom;
}

void Room::SetImageMapRoom(std::string image){
  imageMapRoom = image;
}

std::string Room::GetImageInsideRoom (){
  return imageInsideRoom;
}

void Room::SetImageInsideRoom(std::string image){
  imageInsideRoom = image;
}

bool Room::GetIsSpecialTrainingRoom (){
  return isSpecialTrainingRoom;
}

bool Room::GetIsEnemyRoom (){
  return isEnemyRoom;
}

bool Room::GetIsSleepRoom (){
  return isSleepRoom;
}

int Room::GetElement (){
  return element;
}

std::shared_ptr<Room>& Room::GetNextRoom(){
  return nextRoom;
}

void Room::SetNextRoom(std::shared_ptr<Room> newNextRoom){
  auto next(newNextRoom);
  Room* currentRoom;
  currentRoom = this;

  while (next && next.get() != currentRoom){
    next = next->GetNextRoom();
  }

  if (next){
    throw "Loop Detected";
  } else {
    this->nextRoom = newNextRoom;
  }
}

int Room::GetEntityTurn(){
  return entityTurn;
}
void Room::SetEntityTurn(int entityTurn){
  if ((isSleepRoom || isSpecialTrainingRoom) && entityTurn >= 0 && entityTurn < 2){
    this -> entityTurn  = entityTurn;
  } else if (isEnemyRoom && entityTurn >=0 && entityTurn < 5){
    this -> entityTurn = entityTurn;
  }
}
    // Setters and Getters

    //virtual classes

int Room::GetHeal(){
  std::cout << "methode mère" << std::endl;
  return 0;
}


std::vector<std::unique_ptr<Enemy>>& Room::GetEnemies(){
  std::cout << "methode mère" << std::endl;
  std::vector<std::unique_ptr<Enemy>> enemy; //this will never be used
  return enemy;
}

std::vector<DeckParts*> Room::GetHands(){
  std::cout << "methode mère" << std::endl;
  return std::vector<DeckParts*>();
}

std::vector<DeckParts*> Room::GetDrawPiles(){
  std::cout << "methode mère" << std::endl;
  return std::vector<DeckParts*>();
}

std::vector<DeckParts*> Room::GetDiscardPiles(){
  std::cout << "methode mère" << std::endl;
  return std::vector<DeckParts*>();
}

std::vector<Card*> Room::GetCardReward(){
  std::cout << "methode mère" << std::endl;
  return std::vector<Card*>();
}

void Room::SetHands(std::vector<DeckParts*> hands){}
void Room::SetDiscardPiles(std::vector<DeckParts*> discardPiles){}
void Room::SetDrawPiles(std::vector<DeckParts*> drawPiles){}


void Room::SetTurn(int entityNb){}

std::vector<Card*> Room::GetReward(){return{};}
void Room::SetReward(std::vector<Card*>){}

bool Room::GetIsGameLost(){
  std::cout << "methode mère" << std::endl;
  return false;
}

void Room::SetIsGameLost(bool isGameLost){}

bool Room::GetIsFightWon(){
  std::cout << "methode mère" << std::endl;
  return false;
}

void Room::SetIsFightWon(bool isFightWon){}

int Room::GetTurn(){
  return 0;
}
