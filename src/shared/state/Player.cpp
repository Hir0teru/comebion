#include "Player.h"

using namespace state;


//Player::Player() : Entity(){}
// int energy;
// std::shared_ptr<Deck> deck;

int Player::GetEnergy (){
  return energy;
}
void Player::SetEnergy (int newEnergy){
  energy = newEnergy;
}
std::shared_ptr<Deck> Player::GetDeck (){
  return deck;
}
void Player::SetDeck (std::shared_ptr<Deck> newDeck){
  deck = newDeck;
}
