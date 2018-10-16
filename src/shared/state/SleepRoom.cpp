#include "SleepRoom.h"

using namespace state;


SleepRoom::SleepRoom(): Room(0, "air", false, false, true), heal(10)
{

}

SleepRoom::SleepRoom(int roomNumber, std::string element, int heal_amount): Room(roomNumber, element, false, false, true), heal(heal_amount)
{

}

int SleepRoom::GetHeal(){
  return heal;
}

void SleepRoom::SetHeal(int new_heal){
  heal = new_heal;
}
