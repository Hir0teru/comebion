#include "Card.h"
#include <iostream>

using namespace state;

Card::Card (std::string type, std::string element){
  name = type;
  /// Coût de la carte en energie
  cost = 1;
  /// Type de cible visée (0: joueur, 1: monstre, 2: tous les monstres, 3: tous les joueurs)
  target = 1;
  /// Image représentant la carte

  /// Element de la carte (air, eau, terre, feu, pas d'element)
  element = element;
  /// Dégats de la carte
  if (type == "basic attack"){
    attack = 5;
    block = 0;
    image = "/home/ombre/Documents/Projet/comebion/res/textures/cards/bending/air_bending/1.png";
  }
  /// Nombre de block créé par la carte (à destination du joueur)
  else {
    block = 5;
    attack = 0;
    image = "/home/ombre/Documents/Projet/comebion/res/textures/cards/bending/air_bending/2.png";
  }

  /// Nombre de cartes pichées
  draw = 0;
  /// Nombre de cartes défaussées
  discard = 0;
  /// nombre de point de vie du joueur soignés
  heal = 0;
  /// liste de débuffs appliqués
  // debuffs = std::vector<std::shared_ptr<Debuff>> ();
  // /// liste de buffs appliqués
  // buffs = std::vector<std::shared_ptr<Buff>> ();
};

Card::Card (  std::string name, int cost, int target, std::string image, std::string element,
  int attack, int block, int draw, int discard,  int heal, Debuff debuff, Buff buff){

  this -> name = name;
  /// Coût de la carte en energie
  if (cost < 0){
    std::cout<<"error with cost "<< cost <<std::endl;
    this -> cost = 1;
  }
  else{
    this -> cost = cost;
  }
  /// Type de cible visée (0: joueur, 1: monstre, 2: tous les monstres, 3: tous les joueurs)
  if (target < 0 or target > 3){
    std::cout<<"error with target "<< target <<std::endl;
    this -> target = 1;
  }
  else{
    this -> target = target;
  }
  /// Image représentant la carte
  this -> image = image;
  /// Element de la carte (air, eau, terre, feu, pas d'element)
  if (element != "Air" and element != "Water" and element != "Earth" and element != "Fire" and element != "None"){
    std::cout<<"error with element "<< element <<std::endl;
    std::cout << "Acceptable elements are: Air - Water - Earth - Fire - None";
    this -> element = "Air";
  }
  else{
    this -> element = element;
  }
  /// Dégats de la carte
  if (attack < 0){
    std::cout<<"error with attack "<< attack <<std::endl;
    this -> attack = 0;
  }
  else{
    this -> attack = attack;
  }
  /// Nombre de block créé par la carte (à destination du joueur)
  if (block < 0){
    std::cout<<"error with block "<< block <<std::endl;
    this -> block = 0;
  }
  else{
    this -> block = block;
  }

  /// Nombre de cartes piochées
  if (draw < 0){
    std::cout<<"error with draw "<< draw <<std::endl;
    this -> draw = 0;
  }
  else{
    this -> draw = draw;
  }
  /// Nombre de cartes défaussées
  if (discard < 0){
    std::cout<<"error with discard "<< discard <<std::endl;
    this -> discard = 0;
  }
  else{
    this -> discard = discard;
  }
  /// nombre de point de vie du joueur soignés
  if (heal < 0){
    std::cout<<"error with heal "<< heal <<std::endl;
    this -> heal = 0;
  }
  else{
    this -> heal = heal;
  }
  /// liste de débuffs appliqués
  this -> debuff = debuff;
  // /// liste de buffs appliqués
  this -> buff = buff;
};
Card::~Card(){
  std::cout << "Card destroyed" << std::endl;
}

int Card::GetCost (){
  return cost;
};

void Card::SetCost (int cost){
  if (cost < 0){
    std::cout<<"error with cost "<< cost <<std::endl;
    this -> cost = 1;
  }
  else{
    this -> cost = cost;
  }
};

int Card::GetTarget (){
  return target;
};

std::string Card::GetImage (){
  return image;
};

std::string Card::GetElement (){
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

Debuff Card::GetDebuff (){
  return debuff;
};

Buff Card::GetBuff (){
  return buff;
};

// Setters and Getters
