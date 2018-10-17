#include "Enemy.h"

using namespace state;

Enemy::Enemy (){}
Enemy::Enemy (std::string name, int element, std::string image,
  int statAttack, int statBlock, int life, int id, std::vector<std::shared_ptr<EnemySkill>> skills) : Entity(name, element,
    image,statAttack, statBlock, false,  life,  id){
      reward.reserve(3);
      for (int i = 0; i<3; i++){
        reward[i].reset(new Card("reward", element));
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
  this->intent = newIntent;
}

std::vector<std::shared_ptr<Card>> Enemy::GetReward (){
  return reward;
}

void Enemy::SetReward (std::vector<std::shared_ptr<Card>> newReward){
  this->reward = newReward;
}
