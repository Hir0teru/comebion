#include "SpecialTrainingRoom.h"

using namespace state;

SpecialTrainingRoom::SpecialTrainingRoom (): Room(0, true, false, false)
{

}

SpecialTrainingRoom::~SpecialTrainingRoom()
{

}

SpecialTrainingRoom::SpecialTrainingRoom (int element, std::vector<std::shared_ptr<Card>> cardReward): Room(element, true, false, false)
{
  if (cardReward.size() != 3) {
    throw std::out_of_range("CardReward length should be 3");
  } else {
    this->cardReward = cardReward;
  }
}

std::vector<std::shared_ptr<Card>> SpecialTrainingRoom::GetCardReward (){
  return cardReward;
}
