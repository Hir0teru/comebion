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

Entity::Entity (std::string name, int element, std::string image, int statAttack, int statBlock, bool isPlayer, int life, int id, int maxLife){
  this->name = name;
  if (id < 0){
    throw std::out_of_range("Id cannot be negative");
  }
  else{
    this -> id = id;
  }
  this -> isPlayer = isPlayer;
  if (element < 0 || element > 4){
    this -> element = 0;
  }
  else{
    this -> element = element;
  }
  this -> image = image;

  if (statAttack < 0 ){
    this -> statAttack = 0;
  }
  else{
    this -> statAttack = statAttack;
  }

  if (statBlock < 0) {
    this -> statBlock = 0;
  }
  else{
    this -> statBlock = statBlock;
  }
  if (life < 0) {
    this -> life = 60;
  }
  else {
    this -> life = life;
  }
  block = 0;
  isEntityAlive = true;

  if (maxLife < 0){
    this->maxLife = 60;
  } else {
    this->maxLife = maxLife;
  }
}

int Entity::GetLife (){
  return life;
}

void Entity::SetLife (int newLife){
  if (newLife < 0) {
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
    std::invalid_argument("Id cannot be negative.");
  }
  else{
    this -> id = newId;
  }
}

int Entity::GetElement (){
  return element;
}

void Entity::SetElement (int newElement){
  if (newElement < 0 || newElement > 4){
    this->element = 0;
  }
  else{
    this->element = newElement;
  }
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
  if (newStatAttack < 0 ){
    this -> statAttack = 0;
  }
  else{
    this -> statAttack = newStatAttack;
  }
}

int Entity::GetStatBlock (){
  return statBlock;
}

void Entity::SetStatBlock (int newStatBlock){
  if (newStatBlock < 0) {
    this -> statBlock = 0;
  }
  else{
    this -> statBlock = newStatBlock;
  }
}

Buff Entity::GetBuff (){
  return buff;
}

void Entity::SetBuff (Buff newBuff){
  this->buff = newBuff;
}

Debuff Entity::GetDebuff (){
  return debuff;
}

void Entity::SetDebuff (Debuff newDebuff){
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
  if (newBlock < 0) {
    this -> block = 0;
  }
  else{
    this -> block = newBlock;
  }
}

std::string Entity::GetName(){
  return name;
}

void Entity::SetName(std::string name){
  this->name = name;
}

int Entity::GetMaxLife(){
  return maxLife;
}

void Entity::SetMaxLife(int maxLife){
  this -> maxLife = maxLife;
}

bool Entity::GetIsEntityAlive(){
  return isEntityAlive;
}
void Entity::SetIsEntityAlive(bool isEntityAlive){
  this -> isEntityAlive = isEntityAlive;
}
