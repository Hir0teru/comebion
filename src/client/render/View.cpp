#include "View.h"
#include "engine.h"
#include "state.h"
#include <iostream>

using namespace render;
using namespace engine;




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
          mtx->lock();
          std::cout << "x = " << sf::Mouse::getPosition(window).x << std::endl;
          std::cout << "y = " << sf::Mouse::getPosition(window).y << std::endl;

          if(!gameState -> GetIsInsideRoom()){ //on map
            if((int) sf::Mouse::getPosition(window).x > 505 && (int) sf::Mouse::getPosition(window).x < 620 &&
            (int) sf::Mouse::getPosition(window).y > 505 && (int) sf::Mouse::getPosition(window).y < 535){
                std::cout << "clicked on enter room" << std::endl;
                moteur -> AddCommand(std::make_shared<CommandEnterRoom>()); //salle d'ennemy
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
                   rendu -> UpdateTexturesCards();
                   rendu -> UpdateTexturesPiles();
                   rendu -> DrawInsideRoom();
                   sprite.setTexture(rendu -> GetTexture().getTexture());

              } else if((gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom() ||
                    (gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                     gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon()))&&
                (int) sf::Mouse::getPosition(window).x > 488 && (int) sf::Mouse::getPosition(window).x < 595 &&
                (int) sf::Mouse::getPosition(window).y > 460 && (int) sf::Mouse::getPosition(window).y < 486){
                  std::cout << " clicked on pass" << std::endl;
                  moteur -> AddCommand(std::make_shared<CommandNextEntity>());
                   rendu -> UpdateTexturesCards();
                   rendu -> DrawInsideRoom();
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
                  moteur->AddCommand((std::make_shared<CommandPlayCard>(entityTurn, i, cardSelected)));
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
                  moteur->AddCommand((std::make_shared<CommandPlayCard>(entityTurn, i+2, cardSelected)));
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
              }
            }
        }
        mtx->unlock();
        if(cardSelected == -1){
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
  }
}
