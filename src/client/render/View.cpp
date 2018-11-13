#include "View.h"
#include <iostream>

using namespace render;




View::View (){}

View::View (std::shared_ptr<state::GameState>& gameState){
  rendu = std::make_unique<Rendu>(gameState);
  this -> gameState = gameState;
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
  rendu -> SetTextureRoom();
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

          if(!gameState -> GetIsInsideRoom() &&
            (int) sf::Mouse::getPosition().x > 550 && (int) sf::Mouse::getPosition().x < 660 &&
            (int) sf::Mouse::getPosition().y > 600 && (int) sf::Mouse::getPosition().y < 630){

            }
            std::cout << "x = " << sf::Mouse::getPosition().x << std::endl;
            std::cout << "y = " << sf::Mouse::getPosition().y << std::endl;
            if(cardSelected == -1){  // no card selected
              int i = 0;
              for(auto& card : rendu -> GetTextureCards()){
                if(card -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
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
                (int) sf::Mouse::getPosition().x > 980 && (int) sf::Mouse::getPosition().x < 1090 &&
                (int) sf::Mouse::getPosition().y > 500 && (int) sf::Mouse::getPosition().y < 530){
                  std::cout << " clicked on next turn" << std::endl;
              } else if((gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsSpecialTrainingRoom() ||
                    (gameState ->GetMap() ->  GetFloors()[gameState -> GetMap() -> GetCurrentFloor()] -> GetCurrentRoom() -> GetIsEnemyRoom() &&
                    gameState -> GetMap() -> GetFloors()[gameState ->GetMap() ->  GetCurrentFloor()] -> GetCurrentRoom() -> GetIsFightWon()))&&
                (int) sf::Mouse::getPosition().x > 550 && (int) sf::Mouse::getPosition().x < 660 &&
                (int) sf::Mouse::getPosition().y > 510 && (int) sf::Mouse::getPosition().y < 540){
                  std::cout << " clicked on pass" << std::endl;
              }

            } else{
                int i = 0;
                bool res = false;
                while(!res && i <(int) rendu -> GetTextureCards().size()){
                  if(rendu -> GetTextureCards()[i] -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
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
                  if(rendu -> GetTexturePlayers()[i] -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
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
                  if(rendu -> GetTextureEnemies()[i] -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
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
        // i = 0;
        // for(auto& pile : rendu -> GetTexturePiles()){
        //   if(pile -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
        //     std::cout << "pile " << i<< std::endl;
        //   }
        //   i+=1;
        }
      }
    }
  }
}
