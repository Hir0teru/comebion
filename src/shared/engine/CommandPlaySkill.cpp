#include "CommandPlaySkill.h"
#include "CommandAttack.h"
#include "CommandAddBlock.h"
#include "CommandHeal.h"
#include "CommandAddBuff.h"
#include "CommandAddDebuff.h"
#include "CommandDraw.h"
#include "CommandDiscard.h"
#include "CommandDie.h"
#include "CommandUseEnergy.h"
#include "CommandChangeReward.h"
#include "CommandEndFight.h"
// #include "state/Card.h"
// #include "state/DeckParts.h"
// #include "state/Room.h"
#include "state/PlayerManager.h"
#include "state/SkillManager.h"
#include <iostream>
#include <stdexcept>

using namespace engine;
using namespace state;
using namespace std;

CommandPlaySkill::CommandPlaySkill (){}

CommandPlaySkill::CommandPlaySkill (int enemyID, int targetID, int skillIndex){
  if (enemyID >=2){
    this->enemyID = enemyID;
  } else this->enemyID = 2;
  if (skillIndex >= 0){
    this->skillIndex = skillIndex;
  } else this->skillIndex = 0;
}

void CommandPlaySkill::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Play skill "<<skillIndex<<" from enemy "<<enemyID<<", target is "<<targetID<<endl;

  if (enemyID >= 2){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    SkillManager* SM = SkillManager::instance();
    EnemySkill* selectedSkill = (*SM)[skillIndex];
    PlayerManager* PM = PlayerManager::instance();
    std::vector<Entity*> targets;

    if ((selectedSkill->GetTarget() == 0 || selectedSkill->GetTarget() == 3) && (targetID > 1)){
      throw std::invalid_argument("Wrong target. target should be Player.");
    }

    if ((selectedSkill->GetTarget() == 1 || selectedSkill->GetTarget() == 2) && (targetID < 2)){
      throw std::invalid_argument("Wrong target. target should be Enemy.");
    }

    if (selectedSkill->GetTurnsBeforeUse() > 0) {
      throw std::out_of_range("Skill not ready to be used");
    }

    switch (selectedSkill->GetTarget()){
      case 0:
        targets.push_back((*PM)[targetID]);
        break;
      case 1:
        targets.push_back(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[targetID].get());
        break;
      case 2:
        for (auto& enemy : gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()){
          targets.push_back(enemy.get());
        }
        break;
      case 3:
        for (auto& playerTarget : gameState->GetPlayers()){
          targets.push_back(playerTarget);
        }
        break;
    }

    for (auto& entityTarget : targets){
      CommandAttack commandAttack(selectedSkill->GetAttack(), entityTarget->GetId());
      CommandAddBlock commandAddBlock(selectedSkill->GetBlock(), entityTarget->GetId());
      CommandHeal commandHeal(selectedSkill->GetHeal(), entityTarget->GetId());
      CommandAddBuff commandAddBuff(entityTarget->GetId(), *selectedSkill->GetBuff());
      CommandAddDebuff commandAddDebuff(entityTarget->GetId(), *selectedSkill->GetDebuff());

      commandAttack.Execute(gameState);
      commandAddBlock.Execute(gameState);
      commandHeal.Execute(gameState);
      commandAddBuff.Execute(gameState);
      commandAddDebuff.Execute(gameState);

      if (entityTarget->GetLife() == 0){
        CommandDie commandDie(entityTarget->GetId());
        if (entityTarget->GetIsPlayer()){
          CommandChangeReward commandChangeReward(entityTarget->GetId());
          commandChangeReward.Execute(gameState);
        }
        commandDie.Execute(gameState);

        bool fightWon = true;
        bool isAPlayerAlive = false;
        for (auto& player : gameState->GetPlayers()){
          if (player->GetIsEntityAlive()){
            isAPlayerAlive = true;
          }
        }

        if (!isAPlayerAlive){
          CommandEndFight commandEndFight(false);
          commandEndFight.Execute(gameState);
        }

        for (auto& enemy : gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()){
          if (enemy->GetIsEntityAlive()) {
            fightWon = false;
          }
        }

        if (fightWon){
          CommandEndFight commandEndFight(true);
          commandEndFight.Execute(gameState);
        }
      }
    }
  }
}

void CommandPlaySkill::Undo (std::shared_ptr<state::GameState>& gameState){}
