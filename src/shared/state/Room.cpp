#include "Room.h"

using namespace state;

Room::~Room()
{

}

Room::Room (int elem, bool isSTR, bool isER, bool isSR) {
    // Attributes
    element = elem;
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
      throw "Room has to be either SpecialTrainingRoom or EnemyRoom or SleepRoom";
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

    std::shared_ptr<Room> Room::GetNextRoom(){
      return nextRoom;
    }

    void Room::SetNextRoom(std::shared_ptr<Room> newNextRoom){
      std::shared_ptr<Room> next = newNextRoom;
      std::shared_ptr<Room> currentRoom;
      currentRoom.reset(this);
      while (next != currentRoom && next){
        next = next->nextRoom;
      }
      if (next){
        throw "Loop Detected";
      } else {
        this->nextRoom = newNextRoom;
      }
    }
    // Setters and Getters
