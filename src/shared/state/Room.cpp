#include "Room.h"

using namespace state;

  /// class Room -
Room::Room (int roomNumber, string element, bool isSpecialTrainingRoom, bool isEnemyRoom, bool isSleepRoom) {
    // Attributes
    roomNumber = roomNumber;
    element = element;
    if isSleepRoom{
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg"
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/sleep room.png"
    }
    if isEnemyRoom{
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg"
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/airtemple1.jpg"
    }
    if isEnemyRoom{
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg"
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/air_temple.jpg"
    }

    isSpecialTrainingRoom = isSpecialTrainingRoom;
    isEnemyRoom = isEnemyRoom;
    isSleepRoom = isEnemyRoom;
    // Operations
}

    std::string Room::GetImageMapRoom (){
      return imageMapRoom;
    }
    std::string Room::GetImageInsideRoom (){
      return imageInsideRoom;
    }
    bool Room::GetIsSpecialTrainingRoom (){
      return GetIsSpecialTrainingRoom;
    }
    bool Room::GetIsEnemyRoom (){
      return isEnemyRoom;
    }
    bool Room::GetIsSleepRoom (){
      return isSleepRoom;
    }
    std::string Room::GetElement (){
      return element;
    }
    // Setters and Getters
