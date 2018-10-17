#include "Room.h"

using namespace state;

Room::~Room()
{

}

Room::Room (int roomNb, std::string elem, bool isSTR, bool isER, bool isSR) {
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

    if (isSTR ^ isER ^ isSR){
      isSpecialTrainingRoom = isSTR;
      isEnemyRoom = isER;
      isSleepRoom = isSR;
    } else {
      throw "Room has to be SpecialTrainingRoom XOR EnemyRoom XOR SleepRoom";
    }
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
