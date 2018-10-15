#include "Entity.h"

using namespace state;

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

std::vector<std::shared_ptr<Buff>> Entity::GetBuffs (){
  return buffs;
}

void Entity::SetBuffs (std::vector<std::shared_ptr<Buff>> newBuffs){
  this->buffs = newBuffs;
}

std::vector<std::shared_ptr<Debuff>> Entity::GetDebuffs (){
  return debuffs;
}

void Entity::SetDebuffs (std::vector<std::shared_ptr<Debuff>> newDebuffs){
  this->debuffs = newDebuffs;
}

bool Entity::GetIsPlayer (){
  return isPlayer;
}

void Entity::SetIsPlayer (bool newIsPlayer){
  this->isPlayer = newIsPlayer;
}

bool Entity::GetIsEnemy (){
  return isEnemy;
}

void Entity::SetIsEnemy (bool newIsEnemy){
  this->isEnemy = newIsEnemy;
}

int Entity::GetBlock (){
  return block;
}

void Entity::SetBlock (int newBlock){
  this->block = newBlock;
}
