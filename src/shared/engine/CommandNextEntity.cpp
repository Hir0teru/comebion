#include "CommandNextEntity.h"
#include "state/Buff.h"
#include "state/Debuff.h"
#include "engine.h"
#include <iostream>


using namespace engine;

CommandNextEntity::CommandNextEntity (){}

void CommandNextEntity::Execute (std::shared_ptr<state::GameState>& gameState){
  bool newPT = false;
  bool newET = false;
  bool isAlive = false;
  int nbPlayer = gameState->GetPlayers().size();

  int floorNb = gameState->GetMap()->GetCurrentFloor();
  int entityTurn = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn();
  if(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() && !gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon()){
    int enemyNb = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies().size();
    if (entityTurn >= 0 && entityTurn < 2){ //A player was playing -> discard his hand
      int handSize = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetHands()[entityTurn]->GetSize();

      for(int i = 0; i < handSize; i++){
        CommandDiscard commandDiscard(entityTurn, 0);
        commandDiscard.Execute(gameState);
      }

      if((entityTurn == 0 && ((nbPlayer == 1) || (nbPlayer == 2 && !gameState->GetPlayers()[1]->GetIsEntityAlive()))) || (entityTurn ==1)){ //last player
        entityTurn = 2; // next entity is an enemy
        newET = true;
        isAlive = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetIsEntityAlive();
        while(!isAlive && entityTurn <= enemyNb){
          entityTurn++;
          isAlive = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetIsEntityAlive();
        }
        if (!isAlive){
          newPT = true;
          if(! gameState->GetPlayers()[0]->GetIsEntityAlive()){
            entityTurn = 1;  //one of the two players must be alive, else the game is lost
          } else entityTurn = 0;
        }
      } else entityTurn++; // next player
    }
    else{ // an enemy was playing
      if(entityTurn != enemyNb + 1){
        entityTurn++;
        isAlive = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetIsEntityAlive();
        while(!isAlive && entityTurn <= enemyNb){
          entityTurn++;
          isAlive = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetIsEntityAlive();
        }
        if (!isAlive){
          newPT = true;
          if(! gameState->GetPlayers()[0]->GetIsEntityAlive()){
            entityTurn = 1;  //one of the two players must be alive, else the game is lost
          } else entityTurn = 0;
        }
      } else{
        newPT = true;
        if(! gameState->GetPlayers()[0]->GetIsEntityAlive()){
          entityTurn = 1;  //one of the two players must be alive, else the game is lost
        } else entityTurn = 0;
      }
    }
    if(newPT){ // new turnplayers
      for (int i = 0; i < nbPlayer; i++){
        gameState->GetPlayers()[i]->SetBlock(0);
        gameState->GetPlayers()[i]->SetEnergy(3);
        state::Buff buff = gameState->GetPlayers()[i]->GetBuff();
        buff.SetBlockPlus(buff.GetBlockPlus() - 1);
        buff.SetAttackPlus(buff.GetAttackPlus() - 1);
        gameState->GetPlayers()[i]->SetLife(gameState->GetPlayers()[i]->GetLife() + buff.GetHeal());
        buff.SetHeal(buff.GetHeal() - 1);
        buff.SetEvade(buff.GetEvade() - 1);
        buff.SetRetaliate(buff.GetRetaliate() - 1);
        gameState->GetPlayers()[i]->SetBuff(buff);
        state::Debuff debuff = gameState->GetPlayers()[i]->GetDebuff();
        debuff.SetBlockMinus(debuff.GetBlockMinus() - 1);
        debuff.SetAttackMinus(debuff.GetAttackMinus() - 1);
        gameState->GetPlayers()[i]->SetDebuff(debuff);
      }
    } else if (newET){  // new turn for enemy
      for (int i = 0; i < enemyNb; i++){
        if (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->GetIsEntityAlive()){
          gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->SetBlock(0);
          state::Buff buff = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->GetBuff();
          buff.SetBlockPlus(buff.GetBlockPlus() - 1);
          buff.SetAttackPlus(buff.GetAttackPlus() -1);
          gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->SetLife(gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->GetLife() + buff.GetHeal());
          buff.SetHeal(buff.GetHeal() -1 );
          buff.SetEvade(buff.GetEvade() - 1);
          buff.SetRetaliate(buff.GetRetaliate() -1);
          gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->SetBuff(buff);
          state::Debuff debuff = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->GetDebuff();
          debuff.SetBlockMinus(debuff.GetBlockMinus() - 1);
          debuff.SetAttackMinus(debuff.GetAttackMinus() - 1);
          gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[i]->SetDebuff(debuff);
        }
      }
    }
    if(entityTurn >=0 && entityTurn < 2){
      for(int j = 0; j < 5; j++){
        CommandDraw commandDraw(entityTurn);
        commandDraw.Execute(gameState);
      }
    } else {
      int intent = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetIntent();
      int target = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[entityTurn - 2]->GetSkills()[intent]->GetTarget();
      int cible;
      if(target == 0){
        cible = rand() % (int) (gameState->GetPlayers().size());
        int j =0;
        while(!gameState->GetPlayers()[cible]->GetIsEntityAlive() && j < (int)gameState->GetPlayers().size()){
          cible = rand() % (int) (gameState->GetPlayers().size());
          j++;
        }
        CommandPlaySkill commandSkill(entityTurn, cible, intent);
        commandSkill.Execute(gameState);
      } else if(target == 1 ){
        cible = (rand() % (int) (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies().size())) + 2;
        int j =0;
        while(!gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies()[cible - 2]->GetIsEntityAlive() && j < (int)gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies().size()){
          cible = (rand() % (int) (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies().size())) + 2;
          j++;
        }
        CommandPlaySkill commandSkill(entityTurn, cible, intent);
        commandSkill.Execute(gameState);
      } else if (target == 2){
        CommandPlaySkill commandSkill(entityTurn, 2, intent);
        commandSkill.Execute(gameState);
      } else {
        CommandPlaySkill commandSkill(entityTurn, 0, intent);
        commandSkill.Execute(gameState);
      }
    }
  } else if (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSleepRoom() ||
               gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsSpecialTrainingRoom() ||
               (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsEnemyRoom() &&
              gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetIsFightWon())){
      if(entityTurn == 0 && nbPlayer ==2){
        entityTurn = 1;
      } else {
        entityTurn = 0;
        CommandExitRoom commandExitRoom;
        commandExitRoom.Execute(gameState);
      }

    }
  std::cout<<"Set next entity : " << entityTurn << std::endl;
  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->SetEntityTurn(entityTurn);
}


void CommandNextEntity::Undo (std::shared_ptr<state::GameState>& gameState){}

Json::Value CommandNextEntity::Serialize () {
  Json::Value val;
  val["typeCmd"] = "NextEntity";
  return val;
}
 CommandNextEntity* CommandNextEntity::Deserialize (Json::Value in){
  return this;
}
