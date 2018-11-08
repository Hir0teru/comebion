#include "Moteur.h"
#include <stdexcept>

using namespace engine;

// Operations

Moteur::Moteur (){

}
Moteur::Moteur (std::shared_ptr<state::GameState>& gameState){
  this -> gameState = gameState;
}
Moteur::~Moteur (){}
void Moteur::AddCommand (std::shared_ptr<Command> command){
  commands.push_back(command);
}
void Moteur::Update (){
  if((int) commands.size() > 0){
    commands[0] -> Execute(gameState);
    commands.erase(commands.begin());
  }
}

std::shared_ptr<state::GameState>& Moteur::GetState (){
  return gameState;
}
std::shared_ptr<Command>& Moteur::GetCommand (int ind){
  if (ind < 0 || ind >= (int) commands.size()){
    throw std::invalid_argument("error with command index");
  }
  return commands[ind];
}
void Moteur::ReadCommand (){}

std::vector<std::shared_ptr<Command>> Moteur::GetCommands (){
  return commands;
}
void Moteur::SetCommands (std::vector<std::shared_ptr<Command>> commands){
  this -> commands = commands;
}
