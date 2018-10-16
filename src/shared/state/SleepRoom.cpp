#include "SleepRoom.h"

using namespace state;

<<<<<<< HEAD
// SleepRoom::SleepRoom(int heal_amount){
//   this->heal = heal_amount;
// }
=======
SleepRoom::SleepRoom(int heal_amount){
  this->heal = heal_amount;
}
>>>>>>> 2983e21e38734866593febc5a84205ab0a54f22d

int SleepRoom::GetHeal(){
  return heal;
}

void SleepRoom::SetHeal(int new_heal){
  heal = new_heal;
}
