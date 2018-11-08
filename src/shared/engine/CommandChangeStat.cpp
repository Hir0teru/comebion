#include "CommandChangeStat.h"
#include "state/PlayerManager.h"
#include <iostream>

using namespace state;
using namespace engine;
using namespace std;

CommandChangeStat::CommandChangeStat (int entityID, int statAttack, int statBlock): entityID(entityID), statAttack(statAttack), statBlock(statBlock){}

CommandChangeStat::CommandChangeStat (){}

void CommandChangeStat::Execute (std::shared_ptr<state::GameState>& gameState){
  cout<<"Change stat of entity "<<entityID<<endl;
  cout<<" StatAttack "<< statAttack<< endl;
  cout<<" StatBlock "<< statBlock<< endl;
  Entity* selected_entity = nullptr;
  if (entityID > 0 && entityID < 2){
    PlayerManager* PM = PlayerManager::instance();
    selected_entity = (*PM)[entityID];
  } else {
    int floorNb = gameState->GetMap()->GetCurrentFloor();
    std::vector<std::unique_ptr<Enemy>>& enemies = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEnemies();

    for (auto& enemy : enemies){
      if (enemy.get()->GetId() == entityID){
        selected_entity = enemy.get();
      }
    }
  }

  selected_entity->SetStatAttack(statAttack);
  selected_entity->SetStatBlock(statBlock);
}

void CommandChangeStat::Undo (std::shared_ptr<state::GameState>& gameState){
  cout<<"Undo Change stat of entity "<<entityID<<endl;
  cout<<" StatAttack "<< statAttack<< endl;
  cout<<" StatBlock "<< statBlock<< endl;
  //TODO: ????
}
