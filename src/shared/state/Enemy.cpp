#include "Enemy.h"

using namespace state;

std::vector<std::shared_ptr<EnemySkill>> Enemy::GetSkills (){
  return skills;
}

void Enemy::SetSkills (std::vector<std::shared_ptr<EnemySkill>> newSkills){
  this->skills = newSkills;
}

std::shared_ptr<EnemySkill> Enemy::GetIntent (){
  return intent;
}

void Enemy::SetIntent (std::shared_ptr<EnemySkill> newIntent){
  this->intent = newIntent;
}

std::vector<std::shared_ptr<Card>> Enemy::GetReward (){
  return reward;
}

void Enemy::SetReward (std::vector<std::shared_ptr<Card>> newReward){
  this->reward = newReward;
}
