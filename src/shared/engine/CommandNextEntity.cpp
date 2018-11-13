#include "CommandNextEntity.h"
#include "state/Buff.h"
#include "state/Debuff.h"
#include "CommandDraw.h"
#include "CommandShuffle.h"
#include "CommandPlaySkill.h"
#include <iostream>


using namespace engine;

CommandNextEntity::CommandNextEntity (){}

void CommandNextEntity::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
  int entityTurn =  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEntityTurn() ;
  int enemyNb = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies().size();
  int playerNb = gameState -> GetPlayers().size();

  if(entityTurn == enemyNb +1 ){ // new turn for players
    for (int i = 0; i < playerNb; i++){
      gameState -> GetPlayers()[i] -> SetBlock(0);
      gameState -> GetPlayers()[i] -> SetEnergy(3);
      state::Buff buff = gameState -> GetPlayers()[i] -> GetBuff();
      buff.SetBlockPlus(buff.GetBlockPlus() - 1);
      buff.SetAttackPlus(buff.GetAttackPlus() -1);
      buff.SetHeal(buff.GetHeal() -1 );
      buff.SetEvade(buff.GetEvade() - 1);
      buff.SetRetaliate(buff.GetRetaliate() -1);
      gameState -> GetPlayers()[i] -> SetBuff(buff);
      state::Debuff debuff = gameState -> GetPlayers()[i] -> GetDebuff();
      debuff.SetBlockMinus(debuff.GetBlockMinus() - 1);
      debuff.SetAttackMinus(debuff.GetAttackMinus() - 1);
      gameState -> GetPlayers()[i] -> SetDebuff(debuff);

    }
    if(! gameState -> GetPlayers()[0] -> GetIsEntityAlive()){
      entityTurn = 1;  //one of the two players must be alive, else the game is lost
    } else entityTurn = 0;
  } else if (entityTurn == playerNb - 1){  // new turn for enemy
    entityTurn = 2;
    for (int i = 0; i < enemyNb; i++){
      gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[i] -> SetBlock(0);
      if(! gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[i] -> GetIsEntityAlive()){
        entityTurn += 1;  //one of the two players must be alive, else the game is lost
      }
    }
    if (entityTurn > 5){
      entityTurn = 0;
    }
  }
  else{ entityTurn+=1;}

  if(entityTurn >=0 && entityTurn < 2){
    for(int j = 0; j < 5; j++){
      CommandDraw commandDraw(entityTurn);
      commandDraw.Execute(gameState);
    }
  } else{
      int intent  = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[entityTurn] -> GetIntent();
      int target = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[entityTurn] -> GetSkills()[intent] -> GetTarget();
      int cible;
      if(target == 0){
          cible = rand() % (int) (gameState -> GetPlayers().size());
          int j =0;
          while(!gameState -> GetPlayers()[cible] -> GetIsEntityAlive() && j < (int)gameState -> GetPlayers().size()){
            cible = rand() % (int) (gameState -> GetPlayers().size());
            j++;
          }
          CommandPlaySkill commandSkill(entityTurn, cible, intent);
          commandSkill.Execute(gameState);
        } else if(target == 1 ){
          cible = rand % (int) (gameState -> GetEnemies().size());
          int j =0;
          while(!gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies()[cible] -> GetIsEntityAlive() && j < (int)gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies().size()){
            cible = rand % (int) (gameState -> GetEnemies().size());
            j++;
          }
          CommandPlaySkill commandSkill(entityTurn, cible, intent);
          commandSkill.Execute(gameState);
        } else if (target == 2){
          CommandPlaySkill commandSkill(entityTurn, 2, intent);
          commandSkill.Execute(gameState);
        } else{
          CommandPlaySkill commandSkill(entityTurn, 0, intent);
          commandSkill.Execute(gameState);
        }
}
  std::cout<<"Set next entity : " << entityTurn << std::endl;
  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> SetEntityTurn(entityTurn);
}
void CommandNextEntity::Undo (std::shared_ptr<state::GameState>& gameState){

}
