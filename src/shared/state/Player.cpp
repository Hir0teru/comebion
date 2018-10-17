#include "Player.h"

using namespace state;


Player::Player() : Entity(){}
// int energy;
// std::shared_ptr<Deck> deck;

Player::~Player()
{

}

Player::Player(std::string name, int element, std::string image, int statAttack,
  int statBlock, int life, int id) : Entity(name, element, image,
   statAttack, statBlock, true,  life,  id){
      energy = 3;
      deck.reset(new Deck(element, 10));
    }

int Player::GetEnergy (){
  return energy;
}

void Player::SetEnergy (int newEnergy){
  if (newEnergy < 0){
    throw "Energy should be positive";
  } else {
    energy = newEnergy;
  }
}

std::shared_ptr<Deck> Player::GetDeck (){
  return deck;
}

void Player::SetDeck (std::shared_ptr<Deck> newDeck){
  deck = newDeck;
}
