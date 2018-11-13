#include "View.h"
#include <iostream>

using namespace render;




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

void View::Draw (){
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
  while(window.isOpen()){

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();

    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){

        window.close();
      }
      if(event.type == sf::Event::KeyReleased){
        // moteur -> Update();
        if(!gameState -> GetIsInsideRoom()){
          rendu -> SetTextureMap(1);
          sprite.setTexture(rendu -> GetTextureMap().getTexture());
        }
        else{
          rendu -> SetTextureRoom();
          rendu -> DrawInsideRoom();
          sprite.setTexture(rendu -> GetTexture().getTexture());
          }
        } else if(event.type == sf::Event::MouseButtonReleased){
          std::cout << "x = " << sf::Mouse::getPosition(window).x << std::endl;
          std::cout << "y = " << sf::Mouse::getPosition(window).y << std::endl;

          if(!gameState -> GetIsInsideRoom()){
            if((int) sf::Mouse::getPosition(window).x > 505 && (int) sf::Mouse::getPosition(window).x < 620 &&
            (int) sf::Mouse::getPosition(window).y > 505 && (int) sf::Mouse::getPosition(window).y < 535){
                std::cout << "clicked on next room" << std::endl;
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

              } else if((gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom() ||
                    (gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                    gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon()))&&
                (int) sf::Mouse::getPosition(window).x > 488 && (int) sf::Mouse::getPosition(window).x < 595 &&
                (int) sf::Mouse::getPosition(window).y > 460 && (int) sf::Mouse::getPosition(window).y < 486){
                  std::cout << " clicked on pass" << std::endl;

              } else if(gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSleepRoom() &&
                (int) sf::Mouse::getPosition(window).x > 355 && (int) sf::Mouse::getPosition(window).x < 465 &&
                (int) sf::Mouse::getPosition(window).y > 290 && (int) sf::Mouse::getPosition(window).y < 315){
                  std::cout << " clicked on Heal" << std::endl;

              } else if(gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSleepRoom() &&
                (int) sf::Mouse::getPosition(window).x > 545 && (int) sf::Mouse::getPosition(window).x < 655 &&
                (int) sf::Mouse::getPosition(window).y > 290 && (int) sf::Mouse::getPosition(window).y < 315){
                  std::cout << " clicked on Meditate" << std::endl;
              }

            } else{
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
                  rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                  cardSelected = -1;
                  rendu -> DrawInsideRoom();
                  res = true;
                }
                i+=1;
              }
              i = 0;
              while(!res && i < (int) rendu -> GetTextureEnemies().size()){
                if(rendu -> GetTextureEnemies()[i] -> Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                  std::cout << "enemy " << i<< std::endl;
                  rendu -> GetTextureCards()[cardSelected] -> SetY(rendu -> GetTextureCards()[cardSelected] -> GetY() + 20);
                  cardSelected = -1;
                  rendu -> DrawInsideRoom();
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
      }
    }
  }
}
