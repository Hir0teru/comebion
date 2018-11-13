#include "CommandPlayCard.h"
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
#include <iostream>
#include <stdexcept>

using namespace engine;
using namespace state;

CommandPlayCard::CommandPlayCard (){}

CommandPlayCard::CommandPlayCard (int playerID, int targetID, int cardIndex){
  if (playerID >=0 && playerID < 2){
    this->playerID = playerID;
  } else this->playerID = 0;
  if (cardIndex >= 0 && cardIndex < 7){
    this->cardIndex = cardIndex;
  } else this->cardIndex = 0;
}

void CommandPlayCard::Execute (std::shared_ptr<state::GameState>& gameState){
  if (playerID >= 0 && playerID < 2){
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::shared_ptr<Room>& room = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
    std::vector<Card*> cards = room->GetHands()[playerID]->GetCards();
    Card* selected_card = cards[cardIndex];
    PlayerManager* PM = PlayerManager::instance();
    Player* player = (*PM)[playerID];
    std::vector<Entity*> targets;

    if ((selected_card->GetTarget() == 0 || selected_card->GetTarget() == 3) && (targetID > 1)){
      throw std::invalid_argument("Wrong target. target should be Player.");
    }

    if ((selected_card->GetTarget() == 1 || selected_card->GetTarget() == 2) && (targetID < 2)){
      throw std::invalid_argument("Wrong target. target should be Enemy.");
    }

    if (selected_card->GetCost() > player->GetEnergy()) {
      throw std::out_of_range("Not enough energy to play this card");
    }
    CommandUseEnergy commandUseEnergy(selected_card->GetCost(), playerID);
    commandUseEnergy.Execute(gameState);

    switch (selected_card->GetTarget()){
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
      CommandAttack commandAttack(selected_card->GetAttack(), entityTarget->GetId());
      CommandAddBlock commandAddBlock(selected_card->GetBlock(), entityTarget->GetId());
      CommandHeal commandHeal(selected_card->GetHeal(), entityTarget->GetId());
      CommandAddBuff commandAddBuff(entityTarget->GetId(), *selected_card->GetBuff());
      CommandAddDebuff commandAddDebuff(entityTarget->GetId(), *selected_card->GetDebuff());

      commandAttack.Execute(gameState);
      commandAddBlock.Execute(gameState);
      commandHeal.Execute(gameState);
      commandAddBuff.Execute(gameState);
      commandAddDebuff.Execute(gameState);

      if (entityTarget->GetLife() == 0){
        CommandDie commandDie(entityTarget->GetId());
        if (entityTarget->GetIsPlayer()){
          CommandChangeReward commandChangeReward(entityTarget->GetReward());
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
    CommandDiscard commandDiscard(playerID, cardIndex);
    commandDiscard.Execute(gameState);
    for (int i = 0; i < selected_card->GetDraw(); i++){
      CommandDraw commandDraw(playerID);
      commandDraw.Execute(gameState);
    }
  }
}

void CommandPlayCard::Undo (std::shared_ptr<state::GameState>& gameState){}
