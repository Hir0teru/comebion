#include "View.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "networkManager.h"
#include <stdio.h>
#include <unistd.h>

using namespace render;
using namespace engine;
using namespace networkManager;




View::View (){}

View::View (std::shared_ptr<state::GameState>& gameState, std::shared_ptr<engine::Moteur> moteur){
  rendu = std::make_unique<Rendu>(gameState);
  this -> gameState = gameState;
  this -> moteur = moteur;
}

View::~View (){}

std::unique_ptr<Rendu>& View::GetRendu (){
  return rendu;
}

std::shared_ptr<state::GameState>& View::GetGameState (){
  return gameState;
}

sf::RenderWindow& View::GetWindow (){
  return window;
}

void View::Draw (std::mutex* mtx, bool* pause, bool* run){
  window.create(sf::VideoMode(rendu -> GetDimensionX(), rendu -> GetDimensionY()), "Slay the Avatar");
  // std::cout << "press a key for next step" << std::endl;
  sf::Event event;
  sf::Sprite sprite;
  // rendu -> SetTextureRoom();
  // rendu -> DrawInsideRoom();
  // sprite.setTexture(rendu -> GetTexture().getTexture());
  rendu -> SetTextureMap(1);
  sprite.setTexture(rendu -> GetTextureMap().getTexture());
  int cardSelected = -1;
  while(*run){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
    int entityTurn = gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom()->GetEntityTurn();
    int author = moteur->GetAuthor();
      while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
          *run = false;
          window.close();
        }
        if(event.type == sf::Event::KeyReleased){
            if(!(*pause)){
              *pause = true;
            } else *pause = false;
            } else if(event.type == sf::Event::MouseButtonReleased && !*pause && moteur->GetCommands().empty()){
              if(entityTurn == author){
              mtx->lock();
              // std::cout << "x = " << sf::Mouse::getPosition(window).x << std::endl;
              // std::cout << "y = " << sf::Mouse::getPosition(window).y << std::endl;

              if(!gameState -> GetIsInsideRoom()){ //on map
                if((int) sf::Mouse::getPosition(window).x > 505 && (int) sf::Mouse::getPosition(window).x < 620 &&
                (int) sf::Mouse::getPosition(window).y > 505 && (int) sf::Mouse::getPosition(window).y < 535){
                    std::cout << "clicked on enter room" << std::endl;
                    moteur -> AddCommand(std::make_shared<CommandEnterRoom>()); //salle d'ennemy
                    //sleep(0.3);
                    // moteur -> Update();
                    // rendu -> SetTextureRoom();
                    // rendu -> DrawInsideRoom();
                    // sprite.setTexture(rendu -> GetTexture().getTexture());
                  }
              }
              else{
                if(cardSelected == -1){  // no card selected
                  int i = 0;
                  for(auto& card : rendu -> GetTextureCards()){
                    if(card -> Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                      std::cout << "card " << i<< std::endl;
                      cardSelected = i;
                      card -> SetY(card -> GetY() - 20);
                      rendu -> DrawInsideRoom();
                      sprite.setTexture(rendu -> GetTexture().getTexture());
                      break;
                    }
                    i+=1;
                  }
                  if(gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                      !gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon() &&
                    (int) sf::Mouse::getPosition(window).x > 885 && (int) sf::Mouse::getPosition(window).x < 995 &&
                    (int) sf::Mouse::getPosition(window).y > 655 && (int) sf::Mouse::getPosition(window).y < 688){
                      std::cout << " clicked on next turn" << std::endl;
                      moteur -> AddCommand(std::make_shared<CommandNextEntity>());
                      //moteur -> Update();
                       //rendu -> UpdateTexturesCards();
                       //rendu -> UpdateTexturesPiles();
                       //rendu -> DrawInsideRoom();
                       //sprite.setTexture(rendu -> GetTexture().getTexture());

                  } else if((gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom() ||
                        (gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                         gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon()))&&
                    (int) sf::Mouse::getPosition(window).x > 488 && (int) sf::Mouse::getPosition(window).x < 595 &&
                    (int) sf::Mouse::getPosition(window).y > 460 && (int) sf::Mouse::getPosition(window).y < 486){
                      std::cout << " clicked on pass" << std::endl;
                      moteur -> AddCommand(std::make_shared<CommandNextEntity>());
                       //rendu -> UpdateTexturesCards();
                       //rendu -> DrawInsideRoom();
                      // sprite.setTexture(rendu -> GetTexture().getTexture());

                  }  else if((gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom() ||
                        (gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                        gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon()))&& cardSelected > -1){

                      int entityID = gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom()->GetEntityTurn();
                      moteur -> AddCommand(std::make_shared<CommandAddCard>(entityID, cardSelected, gameState->GetPlayers()[entityID]->GetDeck()->GetCards().size() == 15));
                      moteur -> AddCommand(std::make_shared<CommandNextEntity>());
                  } else if(gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSleepRoom() &&
                    (int) sf::Mouse::getPosition(window).x > 355 && (int) sf::Mouse::getPosition(window).x < 465 &&
                    (int) sf::Mouse::getPosition(window).y > 290 && (int) sf::Mouse::getPosition(window).y < 315){
                      std::cout << " clicked on Heal" << std::endl;
                      int heal = gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom()->GetHeal();
                      int entityID = gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom()->GetEntityTurn();
                      moteur->AddCommand(std::make_shared<CommandHeal>(heal, entityID ));
                      moteur -> AddCommand(std::make_shared<CommandNextEntity>());

                  } else if(gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSleepRoom() &&
                    (int) sf::Mouse::getPosition(window).x > 545 && (int) sf::Mouse::getPosition(window).x < 655 &&
                    (int) sf::Mouse::getPosition(window).y > 290 && (int) sf::Mouse::getPosition(window).y < 315){
                      std::cout << " clicked on Meditate" << std::endl;
                      int entityID = gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom()->GetEntityTurn();
                      int statAttack = gameState->GetPlayers()[entityID]->GetStatAttack();
                      int statBlock= gameState->GetPlayers()[entityID]->GetStatBlock();
                      moteur->AddCommand(std::make_shared<CommandChangeStat>(entityID, statAttack + 2,statBlock + 2));
                      moteur -> AddCommand(std::make_shared<CommandNextEntity>());
                  }

                } else{ // a card was selected
                  int i = 0;
                  bool res = false;
                  while(!res && i <(int) rendu -> GetTextureCards().size()){
                    if(rendu -> GetTextureCards()[i] -> Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                      std::cout << "card " << i<< std::endl;
                      rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                      cardSelected = i;
                      rendu -> GetTextureCards()[i] -> SetY(rendu -> GetTextureCards()[i] -> GetY() - 20);
                      rendu -> DrawInsideRoom();
                      sprite.setTexture(rendu -> GetTexture().getTexture());
                      res = true;
                    }
                    i+=1;
                  }
                  i = 0;
                  while(!res && i < (int) rendu -> GetTexturePlayers().size()){
                    if(rendu -> GetTexturePlayers()[i] -> Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                      std::cout << "player " << i<< std::endl;
                      int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
                      int entityTurn = gameState -> GetMap() ->  GetFloors()[currentFloor]->GetCurrentRoom()->GetEntityTurn();
                      moteur->AddCommand((std::make_shared<CommandPlayCard>(entityTurn, rendu -> GetTexturePlayers()[i]->GetId(), cardSelected)));
                      //rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                      cardSelected = -1;
                      // rendu -> SetTextureRoom();
                      // rendu -> DrawInsideRoom();
                      res = true;
                    }
                    i+=1;
                  }
                  i = 0;
                  while(!res && i < (int) rendu -> GetTextureEnemies().size()){
                    if(rendu -> GetTextureEnemies()[i] -> Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                      std::cout << "enemy " << i<< std::endl;
                      int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
                      int entityTurn = gameState -> GetMap() ->  GetFloors()[currentFloor]->GetCurrentRoom()->GetEntityTurn();
                      //rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                      moteur->AddCommand((std::make_shared<CommandPlayCard>(entityTurn,rendu -> GetTextureEnemies()[i]->GetId() , cardSelected)));
                      cardSelected = -1;
                      //rendu -> SetTextureRoom();
                    //  rendu -> DrawInsideRoom();
                      res = true;
                    }
                    i+=1;
                  }
                  if(!res){
                    rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                    cardSelected = -1;
                    rendu -> DrawInsideRoom();
                    sprite.setTexture(rendu -> GetTexture().getTexture());
                  }
                }
            }
            mtx->unlock();
            if(cardSelected == -1){
              // sleep(0.3);
              // //int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
              // //int entityTurn = gameState -> GetMap() ->  GetFloors()[currentFloor]->GetCurrentRoom()
              // if(gameState->GetIsInsideRoom()){
              //   rendu -> SetTextureRoom();
              //   rendu -> DrawInsideRoom();
              //   sprite.setTexture(rendu -> GetTexture().getTexture());
              // } else{
              //   rendu -> SetTextureMap(1);
              //   sprite.setTexture(rendu -> GetTextureMap().getTexture());
              // }
            }
          }
        }
      }

     if(entityTurn < 2 && entityTurn != author && moteur->GetCommands().empty()){
      NetworkManager* NM = NetworkManager::instance();
      Json::Value test = NM->Get("/command/" + std::to_string(author));
      if(!test.empty()){
        NM->Delete("/command/" + std::to_string(author));
        std::cout << "received :" <<std::endl;
        std::cout << test<< std::endl;
        moteur->ReadCommand(test);
        // sleep(1);
        // if(gameState->GetIsInsideRoom()){
        //   rendu -> SetTextureRoom();
        //   rendu -> DrawInsideRoom();
        //   sprite.setTexture(rendu -> GetTexture().getTexture());
        // } else{
        //   rendu -> SetTextureMap(1);
        //   sprite.setTexture(rendu -> GetTextureMap().getTexture());
        // }
      }
      //  else{
      //   if(gameState->GetIsInsideRoom()){
      //     rendu -> SetTextureRoom();
      //     rendu -> DrawInsideRoom();
      //     sprite.setTexture(rendu -> GetTexture().getTexture());
      //   } else{
      //     rendu -> SetTextureMap(1);
      //     sprite.setTexture(rendu -> GetTextureMap().getTexture());
      //   }
      //   sleep(1);
      // }
    } else if (entityTurn >= 2){
      moteur -> AddCommand(std::make_shared<CommandNextEntity>());
    }
    if(cardSelected == -1){
      // sleep(0.3);
      //int currentFloor = gameState -> GetMap() ->  GetCurrentFloor();
      //int entityTurn = gameState -> GetMap() ->  GetFloors()[currentFloor]->GetCurrentRoom()
      if(gameState->GetIsInsideRoom()){
        rendu -> SetTextureRoom();
        rendu -> DrawInsideRoom();
        sprite.setTexture(rendu -> GetTexture().getTexture());
      } else{
        rendu -> SetTextureMap(1);
        sprite.setTexture(rendu -> GetTextureMap().getTexture());
      }
    }
  }
}


void View::Intro(std::mutex* mtx,bool* pause,bool* run, int* next){
  window.create(sf::VideoMode(rendu -> GetDimensionX(), rendu -> GetDimensionY()), "Slay the Avatar - Intro");
  // std::cout << "press a key for next step" << std::endl;
  sf::Event event;
  sf::Sprite sprite;
  SetIntro();
  sprite.setTexture(introTexture.getTexture());
  *next = -1;
  while(*run && *next == -1){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        *run = false;
        window.close();
      }
      if(event.type == sf::Event::MouseButtonReleased){
          //mtx->lock();
          int x = sf::Mouse::getPosition(window).x;
          int y = sf::Mouse::getPosition(window).y;
          std::cout << "x = " << x << std::endl;
          std::cout << "y = " << y << std::endl;

          if(x >= 105 && x < 215 && y>= 505 && y< 537){
            *next = 0;
            std::cout << "clicked on Solo" << std::endl;
            window.close();
          }
          if(x >= 353 && x < 468 && y>= 505 && y< 537){
            *next = 1;
            std::cout << "clicked on Multi" << std::endl;
            window.close();
          }
          if(x >= 605 && x < 717 && y>= 505 && y< 537){
            *next = 2;
            std::cout << "clicked on 1 IA" << std::endl;
          }
          if(x >= 855 && x < 919 && y>= 505 && y< 537){
            *next = 3;
            std::cout << "clicked on 2 IA" << std::endl;
            window.close();
          }
          //mtx->unlock()
      }
    }
  }
}


void View::SetIntro(){
  if(!introTexture.create(1080, 720)){
    throw std::invalid_argument("error with intro creation");
  }
  int scale = 1.;
  introTexture.clear(sf::Color::Transparent);
  sf::Sprite sprite1;
  sf::Texture texture1;
  sf::Sprite sprite2;
  sf::Texture texture2;
  sf::Sprite sprite3;
  sf::Texture texture3;
  sf::Font font;
  sf::Text text;

  if(!texture1.loadFromFile("res/textures/background/introfin.jpg")){ throw std::invalid_argument("error");}
  sprite1.setTexture(texture1);

  introTexture.draw(sprite1);

  if(!texture2.loadFromFile("res/textures/background/slay the avatar2.png")){ throw std::invalid_argument("error");}
  sprite2.setTexture(texture2);
  sprite2.scale(0.7, 0.7);
  sprite2.setPosition(300, 0);

  introTexture.draw(sprite2);

  if(!texture3.loadFromFile("res/textures/other/button1.png")){ throw std::invalid_argument("error");}
  sprite3.setTexture(texture3);
  sprite3.setPosition(100, 500);
  introTexture.draw(sprite3);
  sprite3.move(250, 0);
  introTexture.draw(sprite3);
  sprite3.move(250, 0);
  introTexture.draw(sprite3);
  sprite3.move(250, 0);
  introTexture.draw(sprite3);

  int x = 138;
  int pas = 250;
  if (!font.loadFromFile("res/text_fonts/attack of the cucumbers.ttf")){throw std::invalid_argument("error");}
  text.setFont(font);
  text.setString("Solo");
  text.setColor(sf::Color::Black);
  text.setCharacterSize(15 * scale);
  text.setStyle(sf::Text::Bold);
  text.move(x * scale, 510 * scale);
  introTexture.draw(text);
  text.move(0 , 2 );
  introTexture.draw(text);
  text.move(2 , 0 );
  introTexture.draw(text);
  text.move(0 , -2 );
  introTexture.draw(text);
  text.setColor(sf::Color::White);
  text.move(-1, 1);
  introTexture.draw(text);

  text.setString("Multi");
  text.setColor(sf::Color::Black);
  text.setCharacterSize(15 * scale);
  text.setStyle(sf::Text::Bold);
  text.move(pas * scale, 0);
  introTexture.draw(text);
  text.move(0 , 2 );
  introTexture.draw(text);
  text.move(2 , 0 );
  introTexture.draw(text);
  text.move(0 , -2 );
  introTexture.draw(text);
  text.setColor(sf::Color::White);
  text.move(-1, 1);
  introTexture.draw(text);

  text.setString("Quitter");
  text.setColor(sf::Color::Black);
  text.setCharacterSize(15 * scale);
  text.setStyle(sf::Text::Bold);
  text.move(pas * scale, 0);
  introTexture.draw(text);
  text.move(0 , 2 );
  introTexture.draw(text);
  text.move(2 , 0 );
  introTexture.draw(text);
  text.move(0 , -2 );
  introTexture.draw(text);
  text.setColor(sf::Color::White);
  text.move(-1, 1);
  introTexture.draw(text);

  text.setString("2 IA");
  text.setColor(sf::Color::Black);
  text.setCharacterSize(15 * scale);
  text.setStyle(sf::Text::Bold);
  text.move(pas * scale, 0);
  introTexture.draw(text);
  text.move(0 , 2 );
  introTexture.draw(text);
  text.move(2 , 0 );
  introTexture.draw(text);
  text.move(0 , -2 );
  introTexture.draw(text);
  text.setColor(sf::Color::White);
  text.move(-1, 1);
  introTexture.draw(text);



  introTexture.display();
}
