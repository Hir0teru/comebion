#include "Room.h"

using namespace state;

  /// class Room -
<<<<<<< HEAD
Room::Room (int roomNb, std::string elem, bool isSTR, bool isER, bool isSR) {
=======
Room::Room (int roomNumber, std::string element, bool isSpecialTrainingRoom, bool isEnemyRoom, bool isSleepRoom) {
>>>>>>> 06293a69453708b7ef9b15ce14ed1f06f29bd7f9
    // Attributes
    roomNumber = roomNb;
    element = elem;
    if (isSR) {
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg";
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/sleep room.png";
    }
    if (isER) {
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg";
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/airtemple1.jpg";
    }
    if (isSTR) {
      imageMapRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/elements.jpg";
      imageInsideRoom = "/home/ombre/Documents/Projet/comebion/res/textures/background/air/air_temple.jpg";
    }

    isSpecialTrainingRoom = isSTR;
    isEnemyRoom = isER;
    isSleepRoom = isSR;
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
    std::string Room::GetElement (){
      return element;
    }
    // Setters and Getters
