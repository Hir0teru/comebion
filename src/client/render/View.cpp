#include "View.h"

using namespace render;




View::View (){}

View::View (std::shared_ptr<state::GameState>& gameState){
  rendu = std::make_unique<Rendu>(gameState);
  this -> gameState = gameState;
  window = std::make_unique<sf::RenderWindow>(sf::VideoMode(rendu -> GetDimensionX(), rendu -> GetDimensionY()), "Slay the Avatar");
}

View::~View (){}

std::unique_ptr<Rendu>& View::GetRendu (){
  return rendu;
}

std::shared_ptr<state::GameState>& View::GetGameState (){
  return gameState;
}

std::unique_ptr<sf::RenderWindow>& View::GetWindow (){
  return window;
}

void View::Draw (){}
