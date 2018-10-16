
#include "Hand.h"


using namespace state;





Hand::Hand ( std::shared_ptr<Player> player) : DeckParts(player, true, false, false){
  sizeMax = 7;
}
int Hand::GetSizeMax (){
  return sizeMax;
}
