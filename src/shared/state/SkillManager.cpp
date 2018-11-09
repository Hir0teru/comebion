#include "SkillManager.h"
#include <iostream>
#include <memory>

using namespace state;

SkillManager* SkillManager::inst;

SkillManager::SkillManager (){
  skills.push_back(std::move(std::make_unique<EnemySkill>(15, 0, 0, std::make_unique<Buff>(0, 0, 0, 0, 0), std::make_unique<Debuff>(0, 0), "res/textures/icons/attack.png", 2, 0)));
  skills.push_back(std::move(std::make_unique<EnemySkill>(0, 0, 10, std::make_unique<Buff>(0, 0, 0, 0, 0), std::make_unique<Debuff>(0, 0), "res/textures/icons/heal.png", 0, 1)));
  skills.push_back(std::move(std::make_unique<EnemySkill>(5, 0, 0, std::make_unique<Buff>(3, 0, 0, 0, 0), std::make_unique<Debuff>(3, 0), "res/textures/icons/attack_down.png", 1, 0)));
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
