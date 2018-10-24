#include "Enemy.h"
#include <iostream>
#include <stdexcept>
#include <memory>
#include "SkillManager.h"


using namespace state;


//basic ennemy for testing
Enemy::Enemy (){
  for (int i = 0; i<3; i++){
    reward.push_back(std::make_shared<Card>("reward", 4));
  }
  SkillManager* SM = SkillManager::instance();
  //TODO: SET ENEMY SKILLS
  skills.push_back((*SM)[0]);
  skills.push_back((*SM)[1]);
  skills.push_back((*SM)[2]);
  intent = 0;
}


Enemy::Enemy (std::string name, int element, std::string image,
  int statAttack, int statBlock, int life, int id, std::vector<EnemySkill*> skills, int maxLife) : Entity(name, element,
    image,statAttack, statBlock, false,  life,  id, maxLife){
      for (int i = 0; i<3; i++){
        reward.push_back(std::make_shared<Card>("reward", element));
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
