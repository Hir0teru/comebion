#include "Entity.h"

using namespace state;


Entity::Entity (){}
Entity::Entity (std::string name, std::string element, std::string image, int statAttack, int statBlock, bool isPlayer, int life, int id){
  this->name = name;
  this -> id = id;
  this -> isPlayer = isPlayer;
  this -> element = element;
  this -> image = image;
  this -> statAttack = statAttack;
  this -> statBlock = statBlock;
  this -> life = life;
  block = 0;
  isEntityAlive = true;
}

int Entity::GetLife (){
  return life;
}

void Entity::SetLife (int newLife){
  this->life = newLife;
}

int Entity::GetId (){
  return id;
}

void Entity::SetId (int newId){
  this->id = newId;
}

std::string Entity::GetElement (){
  return element;
}

void Entity::SetElement (std::string newElement){
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
