#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne


#include "ai.h"
#include "engine.h"
#include "state.h"

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;


void testRecord(){
  time_t seedtime = time(NULL);
  srand(seedtime);
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = std::shared_ptr<Moteur>(new Moteur(gameState, true));
  Json::Value intro;
  intro["seedtime"] = to_string(seedtime);
  moteur->AddJsonValue(intro);

  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;
  int i = 0;

  while(i<500){
    if(moteur->GetCommands().size() <= 0){
      ai1->Play();
      if (moteur->GetCommands().size() <= 0){
          moteur->Update(); // le moteur est toujours vide->un ennemi doit être en train de jouer->passer à l'ennemi suivant
      }
    }
    else{
      std::cout << "updating ..." << std::endl;
      moteur->Update();
      //floorNb =  gameState->GetMap()->GetCurrentFloor();
    //  entityTurn =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn() ;
    //sleep(0.3);
    }
    i++;
  }
  moteur->~Moteur();
  gameState->~GameState();
}


int main(int argc,char* argv[])
{
  SkillManager::instance();
  CardManager::instance();
  PlayerManager::instance();
  time_t seedtime = time(NULL);
  srand(seedtime);
  //Exemple exemple;
  //exemple.setX(53);

  if (argc == 2 and std::string(argv[1]) == "hello")
    cout << "Bonjour le monde !" << endl;
  if (argc == 2 and std::string(argv[1] )== "record")
    testRecord();

    delete SkillManager::instance();
    delete CardManager::instance();
    delete PlayerManager::instance();
    return 0;
}
