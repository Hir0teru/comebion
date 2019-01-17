#include "Player.h"
#include <stdexcept>

using namespace state;


Player::Player() : Entity("Aang", 1, "image.jpg", 0, 0, true, 60, 0, 60){
  energy = 3;
  deck = std::move(std::make_unique<Deck>(1, 10));
}

Player::~Player(){}

Player::Player(std::string name, int element, std::string image, int statAttack,
  int statBlock, int life, int id, int maxLife) : Entity(name, element, image,
   statAttack, statBlock, true,  life,  id, maxLife){
      energy = 3;
      deck = std::move(std::make_unique<Deck>(element, 10));
}

int Player::GetEnergy (){
  return energy;
}

void Player::SetEnergy (int newEnergy){
  if (newEnergy < 0){
    throw std::invalid_argument("Energy should be positive");
  } else {
    energy = newEnergy;
  }
}

Deck* Player::GetDeck (){
  return deck.get();
}

void Player::SetDeck (std::unique_ptr<Deck> newDeck){
  if (newDeck->GetSize() > deck->GetSizeMax()){
    throw std::invalid_argument("new Deck too big");
  }
  else{
    deck=std::move(newDeck);
  }
}

int Player::GetNetworkID(){
  return networkID;
}

void Player::SetNetworkID(int networkID){
  this->networkID = networkID;
}
