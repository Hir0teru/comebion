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
  rendu -> DrawInsideRoom();
  sprite.setTexture(rendu -> GetTexture().getTexture());
  // rendu -> SetTextureMap(1);
  // sprite.setTexture(rendu -> GetTextureMap().getTexture());

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
        if(!rendu -> GetGameState() -> GetIsInsideRoom()){
          rendu -> SetTextureMap(1);
          sprite.setTexture(rendu -> GetTextureMap().getTexture());
        }
        else{
          rendu -> SetTextureRoom();
          rendu -> DrawInsideRoom();
          sprite.setTexture(rendu -> GetTexture().getTexture());
          }
        } else if(event.type == sf::Event::MouseButtonReleased){
          std::cout << "x = " << sf::Mouse::getPosition().x << std::endl;
          std::cout << "y = " << sf::Mouse::getPosition().y << std::endl;
          int i = 0;
          for(auto& card : rendu -> GetTextureCards()){
            if(card -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
              std::cout << "card " << i<< std::endl;
            }
            i+=1;
          }
        i = 0;
        for(auto& player : rendu -> GetTexturePlayers()){
          if(player -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
            std::cout << "player " << i<< std::endl;
          }
          i+=1;
        }
        i = 0;
        for(auto& enemy : rendu -> GetTextureEnemies()){
          if(enemy -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
            std::cout << "enemy " << i<< std::endl;
          }
          i+=1;
        }
        i = 0;
        for(auto& pile : rendu -> GetTexturePiles()){
          if(pile -> Click(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
            std::cout << "pile " << i<< std::endl;
          }
          i+=1;
        }
      }
    }
  }
}
