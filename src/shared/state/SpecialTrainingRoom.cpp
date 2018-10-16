#include "SpecialTrainingRoom.h"

using namespace state;

SpecialTrainingRoom::SpecialTrainingRoom (): Room(0, "air", true, false, false)
{

}
SpecialTrainingRoom::SpecialTrainingRoom (int roomNumber, std::string element, std::vector<std::shared_ptr<Card>> cardReward): Room(roomNumber, element, true, false, false), cardReward(cardReward)
{

}


std::vector<std::shared_ptr<Card>> SpecialTrainingRoom::GetCardReward (){
  return cardReward;
}
