#include "SkillManager.h"
#include <iostream>
#include <memory>

using namespace state;

SkillManager* SkillManager::inst;

SkillManager::SkillManager (){
  skills.push_back(std::move(std::make_unique<EnemySkill>(15, 0, 0, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(0, 0), "imageIntent.jpg", 2, 0)));
  skills.push_back(std::move(std::make_unique<EnemySkill>(0, 0, 10, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(0, 0), "imageIntent.jpg", 0, 0)));
  skills.push_back(std::move(std::make_unique<EnemySkill>(5, 0, 0, std::make_shared<Buff>(0, 0, 0, 0, 0), std::make_shared<Debuff>(2, 0), "imageIntent.jpg", 1, 0)));
}

SkillManager* SkillManager::instance (){
  if (!inst){
    inst = new SkillManager();
  }
  return inst;
}

EnemySkill* SkillManager::operator[] (int i){
  return skills[i].get();
}
