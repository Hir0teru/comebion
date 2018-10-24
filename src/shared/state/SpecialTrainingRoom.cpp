#include "SpecialTrainingRoom.h"

using namespace state;

SpecialTrainingRoom::SpecialTrainingRoom (): Room(0, true, false, false)
{

}

SpecialTrainingRoom::~SpecialTrainingRoom()
{

}

SpecialTrainingRoom::SpecialTrainingRoom (int element, std::vector<Card*> cardReward): Room(element, true, false, false)
{
  if (cardReward.size() != 3) {
    throw std::out_of_range("CardReward length should be 3");
  } else {
    this->cardReward = cardReward;
  }
}

std::vector<Card*> SpecialTrainingRoom::GetCardReward (){
  return cardReward;
}
