// Generated by dia2code
#ifndef STATE__SLEEPROOM__H
#define STATE__SLEEPROOM__H


namespace state {
  class Room;
}

#include "Room.h"

namespace state {

  /// class SleepRoom - 
  class SleepRoom : public state::Room {
    // Attributes
  private:
    int heal;
    // Operations
  public:
    SleepRoom (int heal_amount);
    int GetHeal ();
    void SetHeal (int );
    // Setters and Getters
  };

};

#endif
