#include "CardManager.h"
#include <iostream>
#include <memory>

using namespace state;

CardManager* CardManager::inst;

CardManager::CardManager (){
  // Card::Card (std::string name, int cost, int target, std::string image, int element, int attack, int block, int draw, int discard,  int heal, std::shared_ptr<Debuff> debuff, std::shared_ptr<Buff> buff)
  cards.push_back(std::move(std::make_unique<Card>("Basic Attack", 1, 1, "res/textures/icons/attack.png", 1, 6, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Basic Block", 1, 0, "res/textures/icons/block.png", 2, 0, 5, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Draw", 1, 0, "res/textures/icons/special_training.png", 3, 0, 0, 1, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Discard", 1, 0, "res/textures/icons/debuff.png", 4, 0, 0, 0, 1, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Heal", 1, 3, "res/textures/icons/heal.png", 1, 0, 0, 0, 0, 1, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("BlockMinus", 1, 2, "res/textures/icons/block_down.png", 2, 0, 0, 0, 0, 0, std::make_unique<Debuff>(1,0), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("AttackMinus", 1, 2, "res/textures/icons/attack_down.png", 3, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,1), std::make_unique<Buff>(0,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("BlockPlus", 1, 3, "res/textures/icons/block_up.png", 4, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(1,0,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("AttackPlus", 1, 0, "res/textures/icons/attack_up.png", 1, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,1,0,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Restauration", 1, 0, "res/textures/icons/heal_buff.png", 2, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,1,0,0))));
  cards.push_back(std::move(std::make_unique<Card>("Evade", 1, 0, "res/textures/icons/evade.png", 3, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,1,0))));
  cards.push_back(std::move(std::make_unique<Card>("Retaliate", 1, 0, "res/textures/icons/retaliate.png", 4, 0, 0, 0, 0, 0, std::make_unique<Debuff>(0,0), std::make_unique<Buff>(0,0,0,0,1))));
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
