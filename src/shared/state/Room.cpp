#include "Room.h"
#include <iostream>
using namespace state;

Room::~Room()
{

}

Room::Room (int elem, bool isSTR, bool isER, bool isSR) {
    // Attributes
    if (elem < 0 || elem > 4) {
      element = 0;
    } else {
      element = elem;
    }

    if (isSR) {
      imageMapRoom = "imageRoom.jpg";
      imageInsideRoom = "imageInsideRoom.png";
    }
    if (isER) {
      imageMapRoom = "imageRoom.jpg";
      imageInsideRoom = "imageInsideRoom.jpg";
    }
    if (isSTR) {
      imageMapRoom = "imageRoom.jpg";
      imageInsideRoom = "imageInsideRoom.jpg";
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

    std::string Room::GetImageInsideRoom (){
      return imageInsideRoom;
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
      std::cout<<"setnextroom"<<std::endl;
      std::shared_ptr<Room> next = newNextRoom;
      std::shared_ptr<Room> currentRoom;
      currentRoom.reset(this);

      while (next && next != currentRoom){
        // std::cout << "1 " <<currentRoom << " --- " << next << std::endl;
        next = next->GetNextRoom();
        // std::cout << "2 " <<currentRoom << " --- " << next << std::endl;
      }

      std::cout<< next <<std::endl;

      if (next){
        std::cout<<"loop"<<std::endl;
        throw "Loop Detected";
      } else {
        this->nextRoom = newNextRoom;
      }
    }
    // Setters and Getters
