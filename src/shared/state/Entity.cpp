#include "Entity.h"
#include <iostream>
#include <stdexcept>

using namespace state;


Entity::Entity ()
{

}

Entity::~Entity()
{

}

Entity::Entity (std::string name, int element, std::string image, int statAttack, int statBlock, bool isPlayer, int life, int id){
  this->name = name;
  if (id < 0){
    std::invalid_argument("Id cannot be negative");
  }
  else{
    this -> id = id;
  }
  this -> isPlayer = isPlayer;
  if (element < 0 || element > 4){
    std::cout << "Error with element. Accepted elements are '0' (None), '1' (Air), '2' (Water), '3' (Earth), '4' (Fire)" << std::endl;
    this -> element = 0;
  }
  else{
    this -> element = element;
  }
  this -> image = image;
  if (statAttack < 0 ){
    std::cout << "SetAttack cannot be negative " << std::endl;
    this -> statAttack = 0;
  }
  else{
    this -> statAttack = statAttack;
  }
  if (statBlock < 0) {
    std::cout << "StatBlock cannot be negative" << std::endl;
    this -> statBlock = 0;
  }
  else{
    this -> statBlock = statBlock;
  }
  if (life < 0) {
    std::cout << "Life cannot be negative - default 60" << std::endl;
    this -> life = 60;
  }
  else {
    this -> life = life;
  }
  block = 0;
  isEntityAlive = true;
}

int Entity::GetLife (){
  return life;
}

void Entity::SetLife (int newLife){
  if (newLife < 0) {
    std::cout << "Life cannot be negative - default 60" << std::endl;
    this -> life = 60;
  }
  else {
    this -> life = newLife;
  }
}

int Entity::GetId (){
  return id;
}

void Entity::SetId (int newId){
  if (newId < 0){
    std::invalid_argument("Id cannot be negative");
  }
  else{
    this -> id = newId;
  }
}

int Entity::GetElement (){
  return element;
}

void Entity::SetElement (int newElement){
  this->element = newElement;
}

std::string Entity::GetImage (){
  return image;
}

void Entity::SetImage (std::string newImage){
  this->image = newImage;
}

int Entity::GetStatAttack (){
  return statAttack;
}

void Entity::SetStatAttack (int newStatAttack){
  this->statAttack = newStatAttack;
}

int Entity::GetStatBlock (){
  return statBlock;
}

void Entity::SetStatBlock (int newStatBlock){
  this->statBlock = newStatBlock;
}

Buff Entity::GetBuffs (){
  return buff;
}

void Entity::SetBuffs (Buff newBuff){
  this->buff = newBuff;
}

Debuff Entity::GetDebuffs (){
  return debuff;
}

void Entity::SetDebuffs (Debuff newDebuff){
  this->debuff = newDebuff;
}

bool Entity::GetIsPlayer (){
  return isPlayer;
}

void Entity::SetIsPlayer (bool newIsPlayer){
  this->isPlayer = newIsPlayer;
}

int Entity::GetBlock (){
  return block;
}

void Entity::SetBlock (int newBlock){
  this->block = newBlock;
}
