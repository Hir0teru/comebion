#include "CardManager.h"
#include <iostream>
#include <memory>

using namespace state;

CardManager* CardManager::inst;

CardManager::CardManager (){
  //buff: blockplus, attackplus, heal, evade, retaliate
  //debuff: blockminus, attackminus
  // Card::Card (std::string name, int cost, int target, std::string image, int element, int attack, int block, int draw, int discard,  int heal, std::shared_ptr<Debuff> debuff, std::shared_ptr<Buff> buff)
  cards.push_back(std::move(std::make_unique<Card>("Basic Attack", 1, 1, "res/textures/icons/attack.png", 1, 5, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Basic Block", 1, 0, "res/textures/icons/block.png", 2, 0, 5, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));

  // air
  cards.push_back(std::move(std::make_unique<Card>("Evade", 3, 0, "res/textures/icons/evade.png", 1, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,2,0))));
  cards.push_back(std::move(std::make_unique<Card>("Quick slash", 0, 1, "res/textures/icons/attack.png", 1, 7, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Quick block", 0, 0, "res/textures/icons/block.png", 1, 0, 6, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Weakening blade", 1, 1, "res/textures/icons/attack_debuff.png", 1, 6, 0, 0, 0, 0, std::make_unique<Debuff>(0,3), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Air cutter", 1, 2, "res/textures/icons/attack_debuff.png", 1, 3, 0, 0, 0, 0, std::make_unique<Debuff>(0,3), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Blow", 1, 2, "res/textures/icons/attack.png", 1, 6, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  //water
  cards.push_back(std::move(std::make_unique<Card>("Basic heal", 2, 0, "res/textures/icons/heal.png", 2, 0, 0, 0, 0, 10, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Water shield", 1, 0, "res/textures/icons/heal_block.png", 2, 0, 5, 0, 0, 5, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Restauration", 1, 0, "res/textures/icons/heal.png", 2, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,5,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Piercing blade", 1, 1, "res/textures/icons/attack_debuff.png", 2, 6, 0, 0, 0, 0, std::make_unique<Debuff>(3,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Water slash", 1, 2, "res/textures/icons/attack_debuff.png", 2, 3, 0, 0, 0, 0, std::make_unique<Debuff>(3,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Group heal", 2, 3, "res/textures/icons/heal_block.png", 2, 0, 7, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,4,0,0))));
  //earth
  cards.push_back(std::move(std::make_unique<Card>("Shield", 2, 0, "res/textures/icons/block.png", 3, 0, 20, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Reinforcement", 1, 0, "res/textures/icons/block_up.png", 3, 0, 8, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(3,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Concentrate", 1, 0, "res/textures/icons/block_up.png", 3, 0, 8, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,3,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Slash", 1, 1, "res/textures/icons/attack.png", 3, 8, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Focus", 1, 3, "res/textures/icons/buff.png", 3, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(3,3,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Shatter", 1, 2, "res/textures/icons/attack.png", 3, 6, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  //fire:
  cards.push_back(std::move(std::make_unique<Card>("Retaliate", 1, 0, "res/textures/icons/retaliate.png", 4, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,3))));
  cards.push_back(std::move(std::make_unique<Card>("Fire shield", 2, 0, "res/textures/icons/retaliate.png", 4, 0, 8, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,2))));
  cards.push_back(std::move(std::make_unique<Card>("Slam", 2, 1, "res/textures/icons/attack.png", 4, 10, 0, 0, 0, 0, std::make_unique<Debuff>(2,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Burn", 2, 1, "res/textures/icons/attack.png", 4, 16, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Break", 2, 2, "res/textures/icons/attack_debuff.png", 4, 6, 0, 0, 0, 0, std::make_unique<Debuff>(3,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Inferno", 2, 2, "res/textures/icons/attack.png", 4, 12, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));

}

CardManager* CardManager::instance (){
  if (!inst){
    inst = new CardManager();
  }
  return inst;
}

Card* CardManager::operator[] (int i){
  return cards[i].get();
}
