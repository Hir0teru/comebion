#include "SleepRoom.h"

using namespace state;

SleepRoom::SleepRoom(int heal_amount){
  heal = heal_amount;
}

int SleepRoom::GetHeal(){
  return heal;
}

void SleepRoom::SetHeal(int new_heal){
  heal = new_heal;
}
