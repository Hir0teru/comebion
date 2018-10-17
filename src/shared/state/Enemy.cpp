#include "Enemy.h"
#include <iostream>
#include <stdexcept>

using namespace state;


//basic ennemy for testing
Enemy::Enemy (){
  reward.reserve(3);
  for (std::shared_ptr<Card> card : reward){
    card.reset(new Card("reward", 4));
  }
  skills.reserve(3);
  Buff* buff1 = new Buff(0, 0,0, 0, 0);
  Debuff* debuff1 = new Debuff (0, 0);
  Debuff* debuff2 = new Debuff (2, 0);
  skills[0].reset(new EnemySkill (15, 0, *buff1, *debuff1, "imageIntent.jpg", 2));
  skills[1].reset(new EnemySkill( 0, 10, *buff1, *debuff1, "imageIntent.jpg", 0));
  skills[2].reset(new EnemySkill(5, 0, *buff1, *debuff2, "imageIntent.jpg0", 1));
  delete(buff1);
  delete(debuff1);
  delete(debuff2);
  intent = 0;
}


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
