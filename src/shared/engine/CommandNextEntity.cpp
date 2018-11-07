#include "CommandNextEntity.h"


using namespace engine;

CommandNextEntity::CommandNextEntity (){}

void CommandNextEntity::Execute (std::shared_ptr<state::GameState>& gameState){
  int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
  int entityTurn =  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEntityTurn() ;
  int enemyNb = gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> GetEnemies().size();
  int playerNb = gameState -> GetPlayers().size();

  if(entityTurn == enemyNb - 1){ // new turn for players
    for (int i = 0; i < playerNb; i++){
      gameState -> GetPlayers()[i] -> SetBlock(0);
    }
    if(! gameState -> GetPlayers()[0] -> GetIsEntityAlive()){
      entityTurn = 1;  //one of the two players must be alive, else the game is lost
    } else entityTurn = 0;
  } else if (entityTurn == playerNb - 1){
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
  gameState -> GetMap() -> GetFloors()[floorNb] -> GetCurrentRoom() -> SetEntityTurn(entityTurn);
}
void CommandNextEntity::Undo (std::shared_ptr<state::GameState>& gameState){

}
