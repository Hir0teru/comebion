#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sys/types.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

#include "ai.h"
#include "engine.h"
#include "render.h"
#include "state.h"
#include "networkManager.h"

using namespace ai;
using namespace engine;
using namespace render;
using namespace state;
using namespace std;
using namespace networkManager;


void engineThreadIA(std::shared_ptr<Moteur> moteur, std::shared_ptr<GameState> gameState, bool* run, bool* pause, mutex* mtx){
  mtx->lock();
  AI_Deep* ai1 = new AI_Deep(gameState, moteur,1);
  mtx->unlock();
  while (*run){
    if (!*pause){
      mtx->lock();
      if(moteur->GetCommands().size() <= 0){
        ai1->Play();
        if (moteur->GetCommands().size() <= 0){
          moteur->Update();
        }
      } else {
        std::cout << "updating ..." << std::endl;
        moteur->Update();
        std::this_thread::sleep_for(0.3s);

      }
      mtx->unlock();
      // sleep(0.3);
      std::this_thread::sleep_for(0.01s);
    }
  }
}

void engineThreadTest(std::shared_ptr<Moteur> moteur, std::shared_ptr<GameState> gameState, bool* run, bool* pause, mutex* mtx){
  //mtx->lock();
  //AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  //mtx->unlock();
  while (*run){
    if (!*pause){
      mtx->lock();
      if(moteur->GetCommands().size() <= 0){
        // ai1->Play();
        // if (moteur->GetCommands().size() <= 0){
        //   moteur->Update();
        // }
      } else {
        std::cout << "updating ..." << std::endl;
        moteur->Update();

      }
      mtx->unlock();
      // sleep(0.3);
      std::this_thread::sleep_for(0.01s);
    }
  }
}

void testRunSolo(){

  //std::cout << "id is " << id <<std::endl;

  mutex* mtx = new mutex;
  bool* run = new bool;
  bool* pause = new bool;
  *run = true;
  *pause = false;
  int* next = new int;
  *next = -1;

  PlayerManager* PM = PlayerManager::instance();
  time_t seedtime = time(NULL);

  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false, false);
  moteur->SetAuthor(0);

  View* view = new View(gameState, moteur);
  // moteur->AddCommand(std::make_shared<CommandEnterRoom>());

  std::thread test(&engineThreadIA, moteur, gameState, run, pause, mtx);
  view->Draw(mtx,pause,run);

  test.join();
  delete run;
  delete pause;
  delete mtx;

}



void testRun(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  Json::Value jsonplayers = NM->Get("/user/-1");
  std::cout<<jsonplayers.toStyledString()<<std::endl;

  int id = NM->GetId();
  //std::cout << "id is " << id <<std::endl;

  mutex* mtx = new mutex;
  bool* run = new bool;
  bool* pause = new bool;
  *run = true;
  *pause = false;
  int* next = new int;
  *next = -1;

  PlayerManager* PM = PlayerManager::instance();
  time_t seedtime = time(NULL);

  Json::Value jsonIn;
  jsonIn["seed"] = seedtime;
  Json::Value jsonOut = NM->Put("/seed", jsonIn);
  srand(jsonOut["seed"].asInt());
  std::cout<<"seed : "<<jsonOut["seed"].asInt();

  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false, true);
  moteur->SetAuthor(id-1);

  View* view = new View(gameState, moteur);
  // moteur->AddCommand(std::make_shared<CommandEnterRoom>());
  // moteur->Update();

  //Json::Value test = NM->Get("/command/1");
  //std::cout << test.toStyledString() << std::endl;
  //need to do : send une seed pour le rand() s'il n'y en n'a pas/récuperer cette seed
  // Json::Value val;
  // std::ifstream file ("replay.txt");
  // file >> val;
  // file.close();
  // std::cout << val[0]["seedtime"].asString() << std::endl;

  //srand(std::stoi(val[0]["seedtime"].asString()));
  std::thread test(&engineThreadTest, moteur, gameState, run, pause, mtx);
  view->Draw(mtx,pause,run);

  test.join();
  delete run;
  delete pause;
  delete mtx;

  NM->Delete("/user/" + std::to_string(NM->GetId()));
  if(id==1) {
    NM->Delete("/command/1");
  } else {NM->Delete("/command/0");}
  jsonplayers = NM->Get("/user/-1");
  std::cout<<jsonplayers.toStyledString()<<std::endl;
  std::cout << "Pressez <entrée> pour terminer" << std::endl;
  (void) getc(stdin);
}

void engineThread2(std::shared_ptr<Moteur> moteur, std::shared_ptr<GameState> gameState, bool* run, bool* pause, mutex* mtx){
  mtx->lock();
  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  ai1->SetNetwork(true);
  mtx->unlock();
  while (*run){
    if (!*pause){
      mtx->lock();
      if(moteur->GetCommands().size() <= 0){
        ai1->Play();
        if (moteur->GetCommands().size() <= 0){
          moteur->Update();
        }
      } else {
        std::cout << "updating ..." << std::endl;
        moteur->Update();

      }
      mtx->unlock();
      // sleep(0.3);
      std::this_thread::sleep_for(0.01s);
    }
  }
}


void testRun2(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  Json::Value jsonplayers = NM->Get("/user/-1");
  std::cout<<jsonplayers.toStyledString()<<std::endl;

  int id = NM->GetId();
  //std::cout << "id is " << id <<std::endl;

  mutex* mtx = new mutex;
  bool* run = new bool;
  bool* pause = new bool;
  *run = true;
  *pause = false;
  int* next = new int;
  *next = -1;

  PlayerManager* PM = PlayerManager::instance();
  time_t seedtime = time(NULL);

  Json::Value jsonIn;
  jsonIn["seed"] = seedtime;
  Json::Value jsonOut = NM->Put("/seed", jsonIn);
  srand(jsonOut["seed"].asInt());
  std::cout<<"seed : "<<jsonOut["seed"].asInt();

  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false, true);
  moteur->SetAuthor(id-1);

  View* view = new View(gameState, moteur);

  std::thread test(&engineThread2, moteur, gameState, run, pause, mtx);
  view->Draw(mtx,pause,run);

  test.join();
  delete run;
  delete pause;
  delete mtx;

  NM->Delete("/user/" + std::to_string(NM->GetId()));
  if(id==1) {
    NM->Delete("/command/1");
  } else {NM->Delete("/command/0");}
  jsonplayers = NM->Get("/user/-1");
  std::cout<<jsonplayers.toStyledString()<<std::endl;
  std::cout << "Pressez <entrée> pour terminer" << std::endl;
  (void) getc(stdin);
}

void testNetwork(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  Json::Value players = NM->Get("/user/-1");
  std::cout<<players.toStyledString()<<std::endl;
  std::cout << "Pressez <entrée> pour continuer" << std::endl;
  (void) getc(stdin);
  NM->Delete("/user/" + std::to_string(NM->GetId()));
  players = NM->Get("/user/-1");
  std::cout<<players.toStyledString()<<std::endl;
  std::cout << "Pressez <entrée> pour terminer" << std::endl;
  (void) getc(stdin);
}

void testLobby(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  Json::Value players = NM->Get("/user/-1");
  // tant que y a pas deux joueurs connectes
  while (players.size() != 2)
  {
    // attendre
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // recuperer le nombre de joueur
    players = NM->Get("/user/-1");
  }
  std::cout<<"Connected with user id "<<NM->GetId()<<std::endl;
  while(1){

  }
}

void testGet(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  std::cout<<"GET request sent"<<std::endl;
  Json::Value out = NM->Get("/version");
  std::cout<<"GET request done"<<std::endl;
  std::cout<<out.toStyledString()<<std::endl;
  std::cout<<"End of connection"<<std::endl;
}

void testPut(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  Json::Value test;
  test["name"] = 42;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  std::cout<<"PUT request sent"<<std::endl;
  Json::Value out = NM->Put("/user", test);
  std::cout<<"PUT request done"<<std::endl;
  std::cout<<out.toStyledString()<<std::endl;
  std::cout<<"End of connection"<<std::endl;
}

void testPost(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  Json::Value test;
  test["name"] = 72;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  std::cout<<"POST request sent"<<std::endl;
  NM->Post("/user/1", test);
  std::cout<<"POST request done"<<std::endl;
  std::cout<<"End of connection"<<std::endl;
}

void testDelete(std::string url, int port){
  std::cout<<"Connection to server"<<std::endl;
  NetworkManager* NM = NetworkManager::instance();
  NM->SetUrl(url);
  NM->SetPort(port);
  NM->InitConnection();
  std::cout<<"DELETE request sent"<<std::endl;
  NM->Delete("/user/1");
  std::cout<<"DELETE request done"<<std::endl;
  std::cout<<"End of connection"<<std::endl;
}

void testMulti(){
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false, false);

  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  AI_Deep* ai2 = new AI_Deep(gameState, moteur, 1);
  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;

  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");

  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool pause = false;

  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  while(window.isOpen()){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        if(pause == false){
          pause = true;
        } else pause = false;
      }
    }

    if(!pause){
      if(moteur->GetCommands().size() <= 0){
        ai1->Play();
        ai2->Play();
        if (moteur->GetCommands().size() <= 0){
            moteur->Update(); // le moteur est toujours vide->un ennemi doit être en train de jouer->passer à l'ennemi suivant
        }
      }
      else{
        std::cout << "updating ..." << std::endl;
        moteur->Update();
        //floorNb =  gameState->GetMap()->GetCurrentFloor();
      //  entityTurn =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn() ;
        if(!rendu->GetGameState()->GetIsInsideRoom()){
          rendu->SetTextureMap(1);
          sprite.setTexture(rendu->GetTextureMap().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        else{
          rendu->SetTextureRoom();
          rendu->DrawInsideRoom();
          sprite.setTexture(rendu->GetTexture().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        sleep(0.3);
      }
    }
  }
}

void testReplay(){
  Json::Value val;
  std::ifstream file ("replay.txt");
  file >> val;
  file.close();
  std::cout << val[0]["seedtime"].asString() << std::endl;

  srand(std::stoi(val[0]["seedtime"].asString()));

  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false);


  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;

  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");

  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool pause = false;


  moteur->ReadCommand(val);

  std::cout << "This is a replay" << std::endl;
  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;
  bool end = false;



  while(window.isOpen() && !end){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        if(pause == false){
          pause = true;
        } else pause = false;
      }
    }

    if(!pause){
      if(moteur->GetCommands().size() > 0){
          moteur->Update(); // le moteur est toujours vide->un ennemi doit être en train de jouer->passer à l'ennemi suivant
          //floorNb =  gameState->GetMap()->GetCurrentFloor();
        //  entityTurn =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn() ;
          if(!rendu->GetGameState()->GetIsInsideRoom()){
            rendu->SetTextureMap(1);
            sprite.setTexture(rendu->GetTextureMap().getTexture());
            window.clear(sf::Color::White);
            window.draw(sprite);
            window.display();
          }
          else{
            rendu->SetTextureRoom();
            rendu->DrawInsideRoom();
            sprite.setTexture(rendu->GetTexture().getTexture());
            window.clear(sf::Color::White);
            window.draw(sprite);
            window.display();
          }
          sleep(0.3);
      } else{
        end = true;
        std::cout << "Reached the end. Thank you for watching." << std::endl;
      }
    }
  }
}

void engineThread(std::shared_ptr<Moteur> moteur, std::shared_ptr<GameState> gameState, bool* run, bool* pause, mutex* mtx){
  mtx->lock();
  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  mtx->unlock();
  while (*run){
    if (!*pause){
      mtx->lock();
      if(moteur->GetCommands().size() <= 0){
        ai1->Play();
        if (moteur->GetCommands().size() <= 0){
          moteur->Update();
        }
      } else {
        std::cout << "updating ..." << std::endl;
        moteur->Update();

      }
      mtx->unlock();
      // sleep(0.3);
      std::this_thread::sleep_for(0.01s);
    }
  }
}

void testThread(){
  mutex* mtx = new mutex;
  bool* run = new bool;

  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false);

  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");
  *run = true;
  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool* pause = new bool;
  *pause = false;
  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  std::thread test(&engineThread, moteur, gameState, run, pause, mtx);
  while(*run){
    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
        *run = false;
      }
      if(event.type == sf::Event::KeyReleased){
        if(!(*pause)){
          *pause = true;
        } else *pause = false;
      }
    }
    if(!(*pause)){
      mtx->lock();
      if(!rendu->GetGameState()->GetIsInsideRoom()){
        rendu->SetTextureMap(1);
        sprite.setTexture(rendu->GetTextureMap().getTexture());
      } else {
        rendu->SetTextureRoom();
        rendu->DrawInsideRoom();
        sprite.setTexture(rendu->GetTexture().getTexture());
      }
      mtx->unlock();
      window.clear(sf::Color::White);
      window.draw(sprite);
      window.display();
    }
  }
  test.join();
  delete run;
  delete pause;
  delete mtx;
}

void testDeepAI(){
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false);

  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;

  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");

  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool pause = false;

  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  while(window.isOpen()){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        if(pause == false){
          pause = true;
        } else pause = false;
      }
    }

    if(!pause){
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
        if(!rendu->GetGameState()->GetIsInsideRoom()){
          rendu->SetTextureMap(1);
          sprite.setTexture(rendu->GetTextureMap().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        else{
          rendu->SetTextureRoom();
          rendu->DrawInsideRoom();
          sprite.setTexture(rendu->GetTexture().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        sleep(0.3);
      }
    }
  }
}

void testHeurAI(){
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState);

  AI_Heuristique* ai1 = new AI_Heuristique(gameState, moteur,0);
  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;

  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");



  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool pause = false;

  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  while(window.isOpen()){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();





    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        if(pause == false){
          pause = true;
        } else pause = false;
      }
    }

    if(!pause){
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
        if(!rendu->GetGameState()->GetIsInsideRoom()){
          rendu->SetTextureMap(1);
          sprite.setTexture(rendu->GetTextureMap().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        else{
          rendu->SetTextureRoom();
          rendu->DrawInsideRoom();
          sprite.setTexture(rendu->GetTexture().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        sleep(0.3);
      }
    }
  }
}

void testRandomAI(){
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState);

  AI_Random* ai1 = new AI_Random(gameState, moteur,0);


  Rendu * rendu = new Rendu(gameState);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");


  // std::cout << "press a key for next step" << std::endl;




  sf::Event event;
  sf::Sprite sprite;
  rendu->SetTextureMap(1);
  sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool pause = false;

  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  while(window.isOpen()){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();





    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        if(pause == false){
          pause = true;
        } else pause = false;
      }
    }

    if(!pause){
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
        if(!rendu->GetGameState()->GetIsInsideRoom()){
          rendu->SetTextureMap(1);
          sprite.setTexture(rendu->GetTextureMap().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        else{
          rendu->SetTextureRoom();
          rendu->DrawInsideRoom();
          sprite.setTexture(rendu->GetTexture().getTexture());
          window.clear(sf::Color::White);
          window.draw(sprite);
          window.display();
        }
        sleep(0.3);
      }
    }
  }
}



void test(){
  mutex* mtx = new mutex;
  bool* run = new bool;

  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = make_shared<Moteur>(gameState, false);

  View* view = new View(gameState, moteur);

  //view->Draw();

  // Rendu * rendu = new Rendu(gameState);
  // sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Slay the Avatar");
  *run = true;
  // sf::Event event;
  // sf::Sprite sprite;
  // rendu->SetTextureMap(1);
  // sprite.setTexture(rendu->GetTextureMap().getTexture());
  bool* pause = new bool;
  *pause = false;
  std::cout << "press a key to pause or unpause" << std::endl;
  sleep(1);
  std::cout << "beginning...." << std::endl;

  std::thread test(&engineThreadTest, moteur, gameState, run, pause, mtx);
  view->Draw(mtx,pause,run);
  // while(*run){
  //   window.clear(sf::Color::White);
  //   window.draw(sprite);
  //   window.display();
  //
  //   while (window.pollEvent(event)){
  //     if (event.type == sf::Event::Closed){
  //       window.close();
  //       *run = false;
  //     }
  //     if(event.type == sf::Event::KeyReleased){
  //       if(!(*pause)){
  //         *pause = true;
  //       } else *pause = false;
  //     }
  //   }
  //   if(!(*pause)){
  //     mtx->lock();
  //     if(!rendu->GetGameState()->GetIsInsideRoom()){
  //       rendu->SetTextureMap(1);
  //       sprite.setTexture(rendu->GetTextureMap().getTexture());
  //     } else {
  //       rendu->SetTextureRoom();
  //       rendu->DrawInsideRoom();
  //       sprite.setTexture(rendu->GetTexture().getTexture());
  //     }
  //     mtx->unlock();
  //     window.clear(sf::Color::White);
  //     window.draw(sprite);
  //     window.display();
  //   }
  // }
  test.join();
  ///viewtest.join();
  delete run;
  delete pause;
  delete mtx;



}

void testEngine(){
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  Rendu* rendu = new Rendu(gameState);
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);
  rendu->GetGameState()->SetPlayers(players);
  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Test image");
  Moteur* moteur = new Moteur(gameState);
  moteur->AddCommand(std::make_shared<CommandEnterRoom>()); //salle d'ennemy


  if(rendu->GetGameState()->GetMap()->GetFloors()[0]->GetCurrentRoom()->GetIsEnemyRoom()){
    moteur->AddCommand(std::make_shared<CommandChangeIntent>(2, 2));
    int entityTurn = 0;
    moteur->AddCommand(std::make_shared<CommandAddDebuff>(2, *new Debuff(6, 7)));
    moteur->AddCommand(std::make_shared<CommandAddBuff>(2, *new Buff(1,2,3,4,5)));

    moteur->AddCommand(std::make_shared<CommandShuffle>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn)); // on pioche 5 cartes
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));



    int index;
    //play cards
    for (index = 0; index < 3; index++){
        moteur->AddCommand(std::make_shared<CommandUseEnergy>(1, entityTurn));
        moteur->AddCommand(std::make_shared<CommandAttack>(6, entityTurn,  2));
        moteur->AddCommand(std::make_shared<CommandAddBlock>(6, entityTurn, 0));
        moteur->AddCommand(std::make_shared<CommandChangeElement>(entityTurn, 4));
        moteur->AddCommand(std::make_shared<CommandDiscard>(entityTurn, 0));


    }
    //discard rest of the hand
    for(index = 0; index < 2; index++){
      moteur->AddCommand(std::make_shared<CommandDiscard>( entityTurn, 0));
    }
    //next player
    // moteur->AddCommand(std::make_shared<CommandNextEntity>());
    entityTurn = 1;
    moteur->AddCommand(std::make_shared<CommandShuffle>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn)); // on pioche 5 cartes
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));
    moteur->AddCommand(std::make_shared<CommandDraw>(entityTurn));

    //play cards
    for (index = 0; index < 3; index++){
        moteur->AddCommand(std::make_shared<CommandUseEnergy>(1, entityTurn));
        moteur->AddCommand(std::make_shared<CommandAttack>(6, entityTurn, 2));
        moteur->AddCommand(std::make_shared<CommandAddBlock>(6, entityTurn, 0));
        moteur->AddCommand(std::make_shared<CommandChangeElement>(entityTurn, 4));
        moteur->AddCommand(std::make_shared<CommandDiscard>(entityTurn, 0));
    }
    //discard rest of the hand
    for(index = 0; index < 2; index++){
      moteur->AddCommand(std::make_shared<CommandDiscard>( entityTurn, 0));
    }
    //next enemy
    // moteur->AddCommand(std::make_shared<CommandNextEntity>());
    entityTurn = 2;

    moteur->AddCommand(std::make_shared<CommandAttack>(rendu->GetGameState()->GetMap()->GetFloors()[0]->GetCurrentRoom()->GetEnemies()[entityTurn - 2 ]->GetSkills()[2]->GetAttack(),entityTurn, 0));
    moteur->AddCommand(std::make_shared<CommandAddBlock>(rendu->GetGameState()->GetMap()->GetFloors()[0]->GetCurrentRoom()->GetEnemies()[entityTurn - 2 ]->GetSkills()[2]->GetBlock(),entityTurn, 2));
    moteur->AddCommand(std::make_shared<CommandAddDebuff>(0, *rendu->GetGameState()->GetMap()->GetFloors()[0]->GetCurrentRoom()->GetEnemies()[entityTurn - 2 ]->GetSkills()[2]->GetDebuff()));

    // moteur->AddCommand(std::make_shared<CommandNextEntity>());
    // moteur->AddCommand(std::make_shared<CommandDie>(0));
    moteur->AddCommand(std::make_shared<CommandDie>(2));


  }
  //exit room
  moteur->AddCommand(std::make_shared<CommandExitRoom>());
  moteur->AddCommand(std::make_shared<CommandChangeRoom>());
  moteur->AddCommand(std::make_shared<CommandEnterRoom>());
  moteur->AddCommand(std::make_shared<CommandAddCard>(0, 0,false));

  moteur->AddCommand(std::make_shared<CommandExitRoom>());
  moteur->AddCommand(std::make_shared<CommandChangeRoom>());
  moteur->AddCommand(std::make_shared<CommandEnterRoom>());
  moteur->AddCommand(std::make_shared<CommandAddCard>(0, 0,false));

  moteur->AddCommand(std::make_shared<CommandExitRoom>());
  moteur->AddCommand(std::make_shared<CommandChangeRoom>());
  moteur->AddCommand(std::make_shared<CommandEnterRoom>());
  moteur->AddCommand(std::make_shared<CommandHeal>(27, 0));
  moteur->AddCommand(std::make_shared<CommandExitRoom>());


std::cout << "press a key for next step" << std::endl;
sf::Event event;
sf::Sprite sprite;
rendu->SetTextureMap(1);
sprite.setTexture(rendu->GetTextureMap().getTexture());

while(window.isOpen()){

  window.clear(sf::Color::White);
  window.draw(sprite);
  window.display();

  while (window.pollEvent(event)){
    if (event.type == sf::Event::Closed){

      window.close();
    }
    if(event.type == sf::Event::KeyReleased){
      moteur->Update();
      if(!rendu->GetGameState()->GetIsInsideRoom()){
        rendu->SetTextureMap(1);
        sprite.setTexture(rendu->GetTextureMap().getTexture());
      }
      else{
        rendu->SetTextureRoom();
        rendu->DrawInsideRoom();
        sprite.setTexture(rendu->GetTexture().getTexture());
        }
      }
    }
  }
}



void testSFML(){
  PlayerManager* PM = PlayerManager::instance();
  CardManager* CM = CardManager::instance();

  Rendu* rendu = new Rendu();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  players.push_back((*PM)[1]);

  std::vector<Card*> cards;
  for(int i = 0; i < 7; i++){
    cards.push_back((*CM)[i]);
  }
  rendu->GetGameState()->SetPlayers(players);
  int floorNb = rendu->GetGameState()->GetMap()->GetCurrentFloor();
  std::shared_ptr<Room>& room = rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
  // if(room->GetIsEnemyRoom()){
  //   room->GetHands()[0]->SetCards(cards);
  //   room->GetDrawPiles()[0]->SetCards(cards);
  //   room->SetEntityTurn(0);
  // }
  //
  // rendu->SetTextureMap(1);
  // //
  // rendu->SetTextureRoom();
  // rendu->DrawInsideRoom();

  sf::RenderWindow window(sf::VideoMode(rendu->GetDimensionX(), rendu->GetDimensionY()), "Test image");
  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
    }


    room = rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->GetCurrentRoom();
    if(room->GetIsEnemyRoom()){
      room->GetHands()[0]->SetCards(cards);
      room->GetDrawPiles()[0]->SetCards(cards);
      room->SetEntityTurn(0);
    }

    rendu->SetTextureRoom();
    rendu->DrawInsideRoom();

    window.clear(sf::Color::White);
    sf::Sprite sprite;
    // sprite.setTexture(rendu->GetTextureMap().getTexture());
    sprite.setTexture(rendu->GetTexture().getTexture());

    window.draw(sprite);
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Blue);
    // window.draw(shape);
    window.display();
    sleep(1);
    // room = room->GetNextRoom();
    if(!room->GetNextRoom()){
      rendu->SetTextureMap(1);
      window.clear(sf::Color::White);
      sprite.setTexture(rendu->GetTextureMap().getTexture());
      window.draw(sprite);
      window.display();
      sleep(0.5);
      if(floorNb == 3){
        rendu->GetGameState()->GetMap()->SetCurrentFloor(0);
        floorNb = rendu->GetGameState()->GetMap()->GetCurrentFloor();
        room = rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->GetFirstRoom();
        rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(room);
      }
      else{
        rendu->GetGameState()->GetMap()->SetCurrentFloor(floorNb + 1);
        floorNb = rendu->GetGameState()->GetMap()->GetCurrentFloor();
        room = rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->GetFirstRoom();
        rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(room);
      }
    }
    else{
      rendu->GetGameState()->GetMap()->GetFloors()[floorNb]->SetCurrentRoom(room->GetNextRoom());
    }

  }
}


void testSFML2() {
  CardManager* CM = CardManager::instance();
  PlayerManager* PM = PlayerManager::instance();
  SkillManager* SM = SkillManager::instance();
  Buff* buff1 = new Buff(1,0,2,0,3);
  Debuff* debuff1 = new Debuff(0,4);

  Buff* buff2 = new Buff(0,5,0,6,0);
  Debuff* debuff2 = new Debuff(7,0);

  Buff* buff3 = new Buff(4,5,0,0,9);
  Debuff* debuff3 = new Debuff(1,0);

  Player* aang = (*PM)[0];
  aang->SetBuff(*buff1);
  aang->SetDebuff(*debuff1);
  aang->SetLife(42);
  aang->SetDebuff(*debuff2);

  Player* korra = (*PM)[1];
  korra->SetBuff(*buff2);
  korra->SetLife(42);
  korra->SetDebuff(*debuff2);

  std::vector<EnemySkill*> skills;
  skills.push_back((*SM)[0]);
  skills.push_back((*SM)[1]);
  skills.push_back((*SM)[2]);

  std::unique_ptr<Enemy> enemy1 = std::make_unique<Enemy>( "La", 2, "res/textures/Enemy/Water/La.png", 5, 2, 502, 1, skills, 800);
  std::unique_ptr<Enemy> enemy2 = std::make_unique<Enemy>("Vaatu", 3, "res/textures/Enemy/Vaatu.png", 10, 0, 450, 2, skills, 900);
  enemy2->SetIntent(2);
  enemy1->SetDebuff(*debuff3);
  enemy2->SetBuff(*buff3);
  enemy2->SetBlock(15);
  LoadTextures* loadTextures = new LoadTextures();

  Editeur* editeur = new Editeur( 10, 10, 1,  (*CM)[0], 5, 5, *loadTextures);

  int a;


  sf::RenderWindow window(sf::VideoMode(800, 600), "Test image");
  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
    }


    window.clear(sf::Color::White);
    sf::Sprite sprite;
    sprite.setTexture(editeur->GetTexture().getTexture());
    window.draw(sprite);
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Blue);
    // window.draw(shape);
    window.display();

    sleep(1);

    a = rand() % 100;

    if(a < 30){
      a = rand()%4;
      editeur->SetEditeurCard(1, (*CM)[a], 5, 9);

    }
    else{
      if ( a < 45){
        editeur->SetEditeurPlayer(1, aang);
      }
      else{
        if (a < 60){
          editeur->SetEditeurPlayer(1, korra);
        }
        else{
          if (a < 80){
            editeur->SetEditeurEnemy(1, enemy1);
          }
          else{
            editeur->SetEditeurEnemy(1, enemy2);
          }
        }
      }
    }


  }

}

// Fin test SFML



void testBuff(){
  std::cout << "#### Test of class Buff ####" << std::endl;
  Buff* buff= new Buff(-1, -1, -1, -1, -1);
  if (buff->GetBlockPlus() < 0){
    delete buff;
    throw "Buff.blockPlus should be > 0";
  }
  if (buff->GetAttackPlus() < 0){
    delete buff;
    throw "Buff.attackPlus should be > 0";
  }
  if (buff->GetHeal() < 0){
    delete buff;
    throw "Buff.heal should be > 0";
  }
  if (buff->GetEvade() < 0){
    delete buff;
    throw "Buff.evade should be > 0";
  }
  if (buff->GetBlockPlus() < 0){
    delete buff;
    throw "Buff.blockPlus should be > 0";
  }
  delete buff;
  std::cout << "#### End test of class Buff ####" << std::endl;
}

void testCard(){
  std::cout << "#### Test of class Card ####" << std::endl;
  Card* card1 = new Card((std::string) "test", -1, -1,0, -1, -1, -1, -1, -1, -1, std::make_unique<Debuff>(), std::make_unique<Buff>());
  Card* card2 = new Card((std::string) "test", -1, 4,0, 5, -1, -1, -1, -1, -1, std::make_unique<Debuff>(), std::make_unique<Buff>());
  if (card1->GetCost() < 0){
    delete card1;
    delete card2;
    throw "Card.cost should be > 0";
  }

  if (card1->GetTarget() < 0 || card2->GetTarget() > 3){
    delete card1;
    delete card2;
    throw "Card.target should be between 0 and 3";
  }

  if (card1->GetElement() < 0 || card2->GetElement() > 4){
    delete card1;
    delete card2;
    throw "Card.element should be between 0 and 4";
  }

  if (card1->GetAttack() < 0){
    delete card1;
    delete card2;
    throw "Card.Attack should be > 0";
  }

  if (card1->GetBlock() < 0){
    delete card1;
    delete card2;
    throw "Card.Block should be > 0";
  }

  if (card1->GetDraw() < 0){
    delete card1;
    delete card2;
    throw "Card.Draw should be > 0";
  }

  if (card1->GetDiscard() < 0){
    delete card1;
    delete card2;
    throw "Card.Discard should be > 0";
  }

  if (card1->GetHeal() < 0){
    delete card1;
    delete card2;
    throw "Card.Heal should be > 0";
  }

  delete card1;
  delete card2;
  std::cout << "#### End test of class Card ####" << std::endl;
}

void testDebuff(){
  std::cout << "#### Test of class Debuff ####" << std::endl;
  Debuff* debuff = new Debuff(-1, -1);

  if (debuff->GetBlockMinus() < 0){
    delete debuff;
    throw "Debuff.BlockMinus should be > 0";
  }

  if (debuff->GetAttackMinus() < 0){
    delete debuff;
    throw "Debuff.AttackMinus should be > 0";
  }
  delete debuff;
  std::cout << "#### End test of class Debuff ####" << std::endl;
}

void testDeck(){
  std::cout << "#### Test of class Deck ####" << std::endl;
  Deck* deck = new Deck(1, 18);
  if (deck->GetSizeMax() < deck->GetSize()){
    delete deck;
    throw "Deck.sizeMax should be > to Deck.size";
  }
  delete deck;
  std::cout << "#### End test of class Deck ####" << std::endl;
}

void testDeckParts(){
  PlayerManager* PM = PlayerManager::instance();
  std::cout << "#### Test of class DeckParts ####" << std::endl;
  try{
    DeckParts* deckpart = new DeckParts((*PM)[0], true, true, true);
    delete deckpart;
    throw std::invalid_argument("no exception detected. Deckpart should be either hand, discardPile or drawPile");
  }
  catch(std::out_of_range){}
  catch(std::invalid_argument){
    std::cout << "no exception detected. Deckpart should be either hand, discardPile or drawPile"<<std::endl;
    throw "no exception detected. Deckpart should be either hand, discardPile or drawPile";
  }
  std::cout << "#### End test of class DeckParts ####" << std::endl;
}

void testEnemyRoom(){
  std::cout << "#### Test of class EnemyRoom ####" << std::endl;
  std::vector<std::unique_ptr<Enemy>> noEnemies;
  std::vector<std::unique_ptr<Enemy>> tooManyEnemies;

  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));
  tooManyEnemies.push_back(std::move(std::make_unique<Enemy>()));

  try{
    delete new EnemyRoom(1, std::move(noEnemies));
    throw std::invalid_argument("No enemies in the room exception not detected");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "No enemies in the room exception not detected"<<std::endl;
    throw "No enemies in the room exception not detected";
  }

  try{
    delete new EnemyRoom(1, std::move(tooManyEnemies));
    throw std::invalid_argument("Too many enemies in the room exception not detected");
  } catch(std::out_of_range){}
  catch(std::invalid_argument){
    std::cout << "Too many enemies in the room exception not detected"<<std::endl;
    throw "Too many enemies in the room exception not detected";
  }
  std::cout << "#### End test of class EnemyRoom ####" << std::endl;
}

void testEnemySkill(){
  std::cout << "#### Test of class EnemySkill ####" << std::endl;
  EnemySkill* enemyskill1;
  EnemySkill* enemyskill2;
  try{
    enemyskill1 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),0, -1, -1);
    throw std::invalid_argument("Invalid Target");
  } catch (std::out_of_range){
    enemyskill1 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),0, -1, 2);
  } catch (std::invalid_argument){
    std::cout << "invalid_target_minus"<<std::endl;
    throw "Invalid target";
  }

  try{
    enemyskill2 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),0, -1, 4);
    throw std::invalid_argument("Invalid Target");
  } catch (std::out_of_range){
    enemyskill2 = new EnemySkill(-1, -1, -1, std::make_unique<Buff>(), std::make_unique<Debuff>(),0, -1, 2);
  } catch (std::invalid_argument){
    std::cout << "invalid_target_plus"<<std::endl;
    throw "Invalid target";
  }

  if (enemyskill1->GetAttack() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Attack can not be <0"<<std::endl;
    throw "EnemySkill.Attack can not be <0";
  }

  if (enemyskill1->GetHeal() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Heal can not be <0"<<std::endl;
    throw "EnemySkill.Heal can not be <0";
  }

  if (enemyskill1->GetBlock() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Block can not be <0"<<std::endl;
    throw "EnemySkill.Block can not be <0";
  }

  if (enemyskill1->GetCooldown() < 0){
    delete enemyskill1;
    delete enemyskill2;
    std::cout << "EnemySkill.Cooldown can not be <0"<<std::endl;
    throw "EnemySkill.Cooldown can not be <0";
  }

  delete enemyskill1;
  delete enemyskill2;
  std::cout << "#### End Test of class EnemySkill ####" << std::endl;
}

void testEntity(){
  std::cout << "#### Test of class Entity ####" << std::endl;
  Entity* entity1;
  Entity* entity2 = new Entity((std::string) "entity1", 4, (std::string) "", -1, -1, true, -1, 1, 60);

  try {
    entity1 = new Entity((std::string) "entity1", -1, (std::string) "", -1, -1, true, -1, -1, 60);
    throw std::invalid_argument("id should not be negative");
  } catch (std::out_of_range){
    entity1 = new Entity((std::string) "entity1", -1, (std::string) "", -1, -1, true, -1, 1, 60);
  }
  catch(std::invalid_argument){
    std::cout << "Entity.id should not be negative" << std::endl;
    throw "Entity.id should not be negative";
  }

  if (entity1->GetElement() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.Element should be between 0 and 4";
  }

  if (entity2->GetElement() >4){
    delete entity1;
    delete entity2;
    throw "Entity.Element should be between 0 and 4";
  }

  if (entity1->GetStatAttack() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.StatAttack should be > 0";
  }

  if (entity1->GetStatBlock() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.StatBlock should be > 0";
  }

  if (entity1->GetLife() < 0){
    delete entity1;
    delete entity2;
    throw "Entity.life should be > 0";
  }
  delete entity1;
  delete entity2;
  std::cout << "#### End test of class Entity ####" << std::endl;
}

void testFloor(){
  std::cout << "#### Test of class Floor ####" << std::endl;
  try{
    delete new Floor(-1, 1);
    throw std::invalid_argument("Floor.floorNumber should be between 0 and 3");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.floorNumber should be between 0 and 3" << std::endl;
    throw "Floor.floorNumber should be between 0 and 3";
  }

  try{
    delete new Floor(4, 1);
    throw std::invalid_argument("Floor.floorNumber should be between 0 and 3");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.floorNumber should be between 0 and 3" << std::endl;
    throw "Floor.floorNumber should be between 0 and 3";
  }

  try{
    delete new Floor(1, -1);
    throw std::invalid_argument("Floor.element should be between 0 and 4");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.element should be between 0 and 4" << std::endl;
    throw "Floor.element should be between 0 and 4";
  }

  try{
    delete new Floor(1, 5);
    throw std::invalid_argument("Floor.element should be between 0 and 4");
  } catch (std::out_of_range) {}
  catch(std::invalid_argument){
    std::cout << "Floor.element should be between 0 and 4" << std::endl;
    throw "Floor.element should be between 0 and 4";
  }
  std::cout << "#### End test of class Floor ####" << std::endl;
}

void testInfoPlayer(){
  std::cout << "#### Test of class InfoPlayer ####" << std::endl;

  try{
    delete new InfoPlayer(0, true);;
    throw std::invalid_argument("Element not valid");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument){
    throw "Element not valid";
  }

  try{
    delete new InfoPlayer(5, true);
    throw std::invalid_argument("Element not valid");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument){
    throw "Element not valid";
  }

  std::cout << "#### End test of class InfoPlayer ####" << std::endl;
}

void testMap(){
  std::cout << "#### Test of class Map ####" << std::endl;

  Map* map = new Map();
  try{
    map->SetCurrentFloor(-1);
    throw std::invalid_argument("Invalid value of floor");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument) {
    std::cout<<"Invalid value of floor <0" << std::endl;
    throw "Invalid value of floor";
  }

  try{
    map->SetCurrentFloor(4);
    throw std::invalid_argument("Invalid value of floor");
  } catch (std::out_of_range) {}
  catch (std::invalid_argument) {
    std::cout<<"Invalid value of floor >3" << std::endl;
    throw "Invalid value of floor";
  }

  std::cout << "#### End test of class Map ####" << std::endl;
}

void testRoom(){
  std::cout << "#### Test of class Room ####" << std::endl;
  Room* room;

  try{
    delete new Room(0, true, true, true);
    throw std::invalid_argument("error: room is STR ant SR and ER");
  } catch (std::out_of_range) {
  } catch (std::invalid_argument) {
    throw "error: room is STR ant SR and ER";
  }

  room = new Room(-1, true, false, false);

  if (room->GetElement() < 0 or room->GetElement() > 4) {
    delete room;
    std::cout << room->GetElement()<<std::endl;
    throw "Element of Room not defined";
  }
  delete room;
  std::cout << "#### End test of class Room ####" << std::endl;
}

void testRules(){
  std::cout << "#### Test of class Rules ####" << std::endl;
  Rules* rules;
  std::vector<std::unique_ptr<InfoPlayer>> infos;
  infos.push_back(std::move(std::make_unique<InfoPlayer>()));

  try{
    delete new Rules(2, std::move(infos));
    throw std::invalid_argument("not enough rules");
  } catch (std::out_of_range){
  } catch (std::invalid_argument){
    throw "not enough rules";
  }
  infos.clear();
  infos.push_back(std::move(std::make_unique<InfoPlayer>()));
  rules = new Rules(-1, std::move(infos));
  if (rules->GetNbPlayers()< 1 || rules->GetNbPlayers()>2){
    throw "invalid Rules.nbPlayer";
  }
  delete rules;
  std::cout << "#### End test of class Rules ####" << std::endl;
}

void testSleepRoom(){
  std::cout << "#### Test of class SleepRoom ####" << std::endl;
  SleepRoom* sleeproom = new SleepRoom(0,-1);

  if (sleeproom->GetHeal() < 0){
    throw "Heal < 0";
  }
  delete sleeproom;
  std::cout << "#### End test of class SleepRoom ####" << std::endl;
}


void testSpecialTrainingRoom(){
  std::cout << "#### Test of class SpecialTrainingRoom ####" << std::endl;
  std::vector<Card*> cardreward;

  try{
    delete new SpecialTrainingRoom(1, cardreward);
    throw std::invalid_argument("The reward should be 3 cards");
  } catch (std::out_of_range){
  } catch (std::invalid_argument){
    throw "The reward should be 3 cards";
  }
  std::cout << "#### End test of class SpecialTrainingRoom ####" << std::endl;
}

void testState(){
  testBuff();
  testCard();
  testDebuff();
  testDeck();
  testDeckParts();
  testEnemyRoom();
  testEnemySkill();
  testEntity();
  testFloor();
  testInfoPlayer();
  testMap();
  testRoom();
  testRules();
  testSleepRoom();
  testSpecialTrainingRoom();

}

void testIntro(std::string url, int port){

  mutex* mtx = new mutex;
  bool* run = new bool;
  bool* pause = new bool;
  *run = true;
  *pause = false;
  int* next = new int;
  *next = -1;

  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState;
  // = std::make_shared<state::GameState>();
  // std::vector<Player*> players;
  // players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  // gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur;
   // = make_shared<Moteur>(gameState, false, false);

  View* view = new View(gameState, moteur);

  view->Intro(mtx, pause, run, next);

  if (*next == 0){
    test();
  } else if (*next == 1){
    testRun(url, port);
  } else if (*next == 2){
    testRunSolo();
  } else if (*next == 3){
    testMulti();
  }
}

int main(int argc,char* argv[])
{
  SkillManager::instance();
  CardManager::instance();
  PlayerManager::instance();
  NetworkManager::instance();
  time_t seedtime = time(NULL);
  srand(seedtime);
  //Exemple exemple;
  //exemple.setX(53);

  if (argc == 2 and std::string(argv[1]) == "hello")
    cout << "Bonjour le monde !" << endl;

  if (argc == 2 and std::string(argv[1]) == "state")
    testState();
  if (argc == 2 and std::string(argv[1])== "render")
    testSFML();
  if (argc == 2 and std::string(argv[1])== "render2")
    testSFML2();
  if (argc == 2 and std::string(argv[1])== "engine")
    testEngine();
  if (argc == 2 and std::string(argv[1])== "test")
    test();
  if (argc == 2 and std::string(argv[1])== "random_ai")
    testRandomAI();
  if (argc == 2 and std::string(argv[1])== "heuristic_ai")
    testHeurAI();
  if (argc == 2 and std::string(argv[1] )== "deep_ai")
    testDeepAI();
  if (argc == 2 and std::string(argv[1])== "deep_ai")
    testDeepAI();
  if (argc == 2 and std::string(argv[1])== "thread")
    testThread();
  if (argc == 2 and std::string(argv[1])== "play")
    testReplay();
  if (argc == 2 and std::string(argv[1])== "multi")
    testMulti();
  if (std::string(argv[1])== "get"){
    if (argc == 2){
      testGet("http://localhost/", 8080);
    } else if (argc == 4){
      testGet(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client get URL PORT. default: bin/client get http://localhost/ 8080"<<std::endl;
    }
  }
  if (std::string(argv[1])== "post"){
    if (argc == 2){
      testPost("http://localhost/", 8080);
    } else if (argc == 4){
      testPost(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client post URL PORT. default: bin/client post http://localhost/ 8080"<<std::endl;
    }
  }
  if (std::string(argv[1])== "put"){
    if (argc == 2){
      testPut("http://localhost/", 8080);
    } else if (argc == 4){
      testPut(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client put URL PORT. default: bin/client put http://localhost/ 8080"<<std::endl;
    }
  }
  if (std::string(argv[1])== "delete"){
    if (argc == 2){
      testDelete("http://localhost/", 8080);
    } else if (argc == 4){
      testDelete(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client delete URL PORT. default: bin/client delete http://localhost/ 8080"<<std::endl;
    }
  }

  if (std::string(argv[1])== "lobby"){
    if (argc == 2){
      testLobby("http://localhost/", 8080);
    } else if (argc == 4){
      testLobby(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client lobby URL PORT. default: bin/client lobby http://localhost/ 8080"<<std::endl;
    }
  }

  // if (std::string(argv[1])== "network"){
  //   if (argc == 2){
  //     testNetwork("http://localhost/", 8080);
  //   } else if (argc == 4){
  //     testNetwork(argv[2], std::stoi(argv[3]));
  //   } else {
  //     std::cout<<"Use bin/client network URL PORT. default: bin/client network http://localhost/ 8080"<<std::endl;
  //   }
  // }

    if (std::string(argv[1])== "network"){
      if (argc == 2){
        testRun("http://localhost/", 8080);
      } else if (argc == 4){
        testRun(argv[2], std::stoi(argv[3]));
      } else {
        std::cout<<"Use bin/client network URL PORT. default: bin/client network http://localhost/ 8080"<<std::endl;
      }
  }
  if (std::string(argv[1])== "intro"){
    if (argc == 2){
      testIntro("http://localhost/", 8080);
    } else if (argc == 4){
      testIntro(argv[2], std::stoi(argv[3]));
    } else {
      std::cout<<"Use bin/client intro URL PORT. default: bin/client intro http://localhost/ 8080"<<std::endl;
    }
  }
  delete SkillManager::instance();
  delete CardManager::instance();
  delete PlayerManager::instance();
  delete NetworkManager::instance();
  return 0;
}
