#include "SleepRoom.h"

using namespace state;


SleepRoom::SleepRoom(): Room(0, false, false, true), heal(10)
{

}

SleepRoom::~SleepRoom()
{

}

SleepRoom::SleepRoom(int element, int heal_amount): Room(element, false, false, true), heal(heal_amount)
{

}

int SleepRoom::GetHeal(){
  return heal;
}

void SleepRoom::SetHeal(int new_heal){
  if (new_heal < 0){
    heal = 0;
  } else {
    heal = new_heal;
  }
}
