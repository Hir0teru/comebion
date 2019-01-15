#include "Card.h"
#include <iostream>

using namespace state;


Card::Card (std::string type, int element){
  name = type;
  /// Coût de la carte en energie
  cost = 1;
  /// Type de cible visée (0: joueur, 1: monstre, 2: tous les monstres, 3: tous les joueurs)
  target = 1;
  /// Image représentant la carte

  /// Element de la carte: 0 none,1 air, 2 water, 3 earth, 4 fire
  if (element < 0 || element > 4){
    this->element = 0;
  }
  else {
    this->element = element;
  }
  /// Dégats de la carte
  if (type == "basic attack"){
    attack = 5;
    block = 0;
    image = 3;
  }
  /// Nombre de block créé par la carte (à destination du joueur)
  else {
    block = 5;
    attack = 0;
    image = 6;
  }

  /// Nombre de cartes pichées
  draw = 0;
  /// Nombre de cartes défaussées
  discard = 0;
  /// nombre de point de vie du joueur soignés
  heal = 0;
  /// liste de débuffs appliqués
  debuff = std::move(std::make_unique<Debuff>());
  /// liste de buffs appliqués
  buff = std::move(std::make_unique<Buff>());
};

Card::Card (std::string name, int cost, int target, int image, int element, int attack, int block, int draw, int discard,  int heal, std::unique_ptr<Debuff> debuff, std::unique_ptr<Buff> buff){

  this->name = name;
  /// Coût de la carte en energie
  if (cost < 0){
    this->cost = 1;
  }
  else{
    this->cost = cost;
  }
  /// Type de cible visée (0: joueur, 1: monstre, 2: tous les monstres, 3: tous les joueurs)
  if (target < 0 or target > 3){
    this->target = 1;
  }
  else{
    this->target = target;
  }
  /// Image représentant la carte
  this->image = image;
  /// Element de la carte (air, eau, terre, feu, pas d'element)
  if (element < 0 || element > 4){
    this->element = 0;
  }
  else{
    this->element = element;
  }
  /// Dégats de la carte
  if (attack < 0){
    this->attack = 0;
  }
  else{
    this->attack = attack;
  }
  /// Nombre de block créé par la carte (à destination du joueur)
  if (block < 0){
    this->block = 0;
  }
  else{
    this->block = block;
  }

  /// Nombre de cartes piochées
  if (draw < 0){
    this->draw = 0;
  }
  else{
    this->draw = draw;
  }
  /// Nombre de cartes défaussées
  if (discard < 0){
    this->discard = 0;
  }
  else{
    this->discard = discard;
  }
  /// nombre de point de vie du joueur soignés
  if (heal < 0){
    this->heal = 0;
  }
  else{
    this->heal = heal;
  }
  /// liste de débuffs appliqués
  this->debuff = std::move(debuff);
  // /// liste de buffs appliqués
  this->buff = std::move(buff);
};
Card::~Card(){
}

int Card::GetCost (){
  return cost;
};

void Card::SetCost (int cost){
  if (cost < 0){
    this->cost = 1;
  }
  else{
    this->cost = cost;
  }
};

int Card::GetTarget (){
  return target;
};

int Card::GetImage (){
  return image;
};

int Card::GetElement (){
  return element;
};

int Card::GetAttack (){
  return attack;
};

int Card::GetBlock (){
  return block;
};

int Card::GetDraw (){
  return draw;
};

int Card::GetDiscard (){
  return discard;
};

int Card::GetHeal (){
  return heal;
};

Debuff* Card::GetDebuff (){
  return debuff.get();
};

Buff* Card::GetBuff (){
  return buff.get();
};

std::string Card::GetName(){
  return name;
}
// Setters and Getters
