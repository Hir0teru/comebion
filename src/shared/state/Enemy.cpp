#include "CardManager.h"
#include "Enemy.h"
#include <iostream>
#include <stdexcept>
#include <memory>
#include "SkillManager.h"
#include <string>


using namespace state;
using namespace std;


//basic ennemy for testing
Enemy::Enemy (){
  CardManager* CM = CardManager::instance();
  // SkillManager* SM = SkillManager::instance();
  int card;
  for (int i = 0; i<3; i++){
    card = rand() % 24 + 2;
    reward.push_back((*CM)[card]);
    // skills.push_back((*SM)[i]);
  }
  intent = 0;
  type = 1;
}





Enemy::Enemy(int element, int nb):Enemy(){
  SkillManager* SM = SkillManager::instance();
  this->type = nb;
  this->SetElement(element);
  this -> SetIsEntityAlive(true);
  this->SetIsPlayer(false);
  this -> SetStatAttack(0);
  this -> SetStatBlock(0);
  this -> SetBlock(0);
  Buff* tmpbuff = new Buff();
  Debuff* tmpdebuff = new Debuff();
  this->SetBuff(*tmpbuff);
  this->SetDebuff(*tmpdebuff);
  delete(tmpbuff);
  delete(tmpdebuff);
  switch (element) {
    case 1:
      if (nb == 0) {
        this->SetImage("res/textures/Enemy/Air/bison.png");
        this->SetName("Flying Bison");
        this->SetMaxLife(200);
        this->SetLife(200);
        skills.push_back((*SM)[8]);
        skills.push_back((*SM)[9]);
        skills.push_back((*SM)[10]);
      } else {
        this->SetImage("res/textures/Enemy/Air/" + to_string(nb) +".png");
        this->SetName("air thing");
        this->SetMaxLife(30);
        this->SetLife(30);
        skills.push_back((*SM)[0]);
        skills.push_back((*SM)[1]);
        skills.push_back((*SM)[2]);
      }
      break;
    case 2:
      if (nb == 0) {
        this->SetImage("res/textures/Enemy/Water/La.png");
        this->SetName("La");
        this->SetMaxLife(500);
        this->SetLife(500);
        skills.push_back((*SM)[11]);
        skills.push_back((*SM)[12]);
        skills.push_back((*SM)[13]);
      } else {
        this->SetImage("res/textures/Enemy/Water/" + to_string(nb) +".png");
        this->SetName("water thing");
        this->SetMaxLife(60);
        this->SetLife(60);
        skills.push_back((*SM)[0]);
        skills.push_back((*SM)[3]);
        skills.push_back((*SM)[4]);
      }
      break;
    case 3:
      if (nb == 0) {
        this->SetImage("res/textures/Enemy/Earth/badgermole.png");
        this->SetName("Badgermole");
        this->SetMaxLife(300);
        this->SetLife(300);
        skills.push_back((*SM)[14]);
        skills.push_back((*SM)[15]);
        skills.push_back((*SM)[16]);
      } else {
        this->SetImage("res/textures/Enemy/Earth/" + to_string(nb) +".png");
        this->SetName("earth thing");
        this->SetMaxLife(60);
        this->SetLife(60);
        skills.push_back((*SM)[0]);
        skills.push_back((*SM)[5]);
        skills.push_back((*SM)[6]);
      }
      break;
    case 4:
      if (nb == 0) {
        this->SetImage("res/textures/Enemy/Fire/blue_dragon.png");
        this->SetName("Blue Dragon");
        this->SetMaxLife(250);
        this->SetLife(250);
        skills.push_back((*SM)[17]);
        skills.push_back((*SM)[18]);
        skills.push_back((*SM)[19]);
      } else if (nb == -1) {
        this->SetImage("res/textures/Enemy/Fire/red_dragon.png");
        this->SetName("Red Dragon");
        this->SetMaxLife(250);
        this->SetLife(250);
        skills.push_back((*SM)[20]);
        skills.push_back((*SM)[21]);
        skills.push_back((*SM)[22]);
      } else {
        this->SetImage("res/textures/Enemy/Fire/" + to_string(nb) +".png");
        this->SetName("fire thing");
        this->SetMaxLife(60);
        this->SetLife(60);
        skills.push_back((*SM)[0]);
        skills.push_back((*SM)[3]);
        skills.push_back((*SM)[7]);
      }
      break;
  }
}


Enemy::Enemy (std::string name, int element, std::string image,
  int statAttack, int statBlock, int life, int id, std::vector<EnemySkill*> skills, int maxLife) : Entity(name, element,
    image,statAttack, statBlock, false,  life,  id, maxLife){
      CardManager* CM = CardManager::instance();
      for (int i = 0; i<3; i++){
        reward.push_back((*CM)[0]);
      }
      this -> skills = skills;
      intent = 0;
  }

Enemy::~Enemy(){}

std::vector<EnemySkill*> Enemy::GetSkills (){
  return skills;
}

void Enemy::SetSkills (std::vector<EnemySkill*> newSkills){
  this->skills = newSkills;
}

int Enemy::GetIntent (){
  return intent;
}

void Enemy::SetIntent (int newIntent){
  int size = skills.size();
  if (newIntent >= size || newIntent < 0){
    this -> intent = 0;

  }
  else {
    this->intent = newIntent;
  }
}

std::vector<Card*> Enemy::GetReward (){
  return reward;
}

void Enemy::SetReward (std::vector<Card*> newReward){
  int size = newReward.size();
  if (size != 3){
    throw std::invalid_argument("There must be 3 reward cards");
  }
  else{
    this->reward = newReward;
  }
}

int Enemy::GetType(){
  return type;
}

void Enemy::SetType(int type){
  this->type = type;
}
