#include "Enemy.h"
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace state;


//basic ennemy for testing
Enemy::Enemy (){
  std::cout<<"1"<<std::endl;
  for (int i = 0; i<3; i++){
    reward.push_back(std::make_shared<Card>("reward", 4));
  }
  std::cout<<"2"<<std::endl;
  skills.push_back(std::make_shared<EnemySkill>(15, 0, 0, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(0, 0), "imageIntent.jpg", 2, 0));
  std::cout<<"3"<<std::endl;
  std::shared_ptr<EnemySkill> test = std::make_shared<EnemySkill>(0, 0, 10, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(0, 0), "imageIntent.jpg", 0, 0);
  std::cout<<"3.1"<<std::endl;
  std::cout<<test<<std::endl;
  skills.push_back(test);
  std::cout<<"4"<<std::endl;
  skills.push_back(std::make_shared<EnemySkill>(5, 0, 0, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(2, 0), "imageIntent.jpg0", 1, 0));
  std::cout<<"5"<<std::endl;
  intent = 0;
}


Enemy::Enemy (std::string name, int element, std::string image,
  int statAttack, int statBlock, int life, int id, std::vector<std::shared_ptr<EnemySkill>> skills) : Entity(name, element,
    image,statAttack, statBlock, false,  life,  id){
      for (int i = 0; i<3; i++){
        reward.push_back(std::make_shared<Card>("reward", element));
      }
      this -> skills = skills;
      intent = 0;
  }


Enemy::~Enemy(){}

std::vector<std::shared_ptr<EnemySkill>> Enemy::GetSkills (){
  return skills;
}

void Enemy::SetSkills (std::vector<std::shared_ptr<EnemySkill>> newSkills){
  this->skills = newSkills;
}

int Enemy::GetIntent (){
  return intent;
}

void Enemy::SetIntent (int newIntent){
  int size = skills.size();
  if (newIntent >= size || newIntent < 0){
    std::cout << "error with newIntent - set to 0" << std::endl;
    this -> intent = 0;

  }
  else {
    this->intent = newIntent;
  }
}

std::vector<std::shared_ptr<Card>> Enemy::GetReward (){
  return reward;
}

void Enemy::SetReward (std::vector<std::shared_ptr<Card>> newReward){
  int size = newReward.size();
  if (size != 3){
    throw std::invalid_argument("There must be 3 reward cards");
  }
  else{
    this->reward = newReward;
  }
}
