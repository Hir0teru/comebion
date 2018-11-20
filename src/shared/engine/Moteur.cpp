#include "Moteur.h"
#include "engine.h"
#include <stdexcept>
#include <iostream>

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
    try{
      commands[0] -> Execute(gameState);
      commands.erase(commands.begin());
    }
    catch(std::invalid_argument){
      std::cout << "wrong command" << std::endl;
      commands.erase(commands.begin());
    }

  } else{
    int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
    if (gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetEntityTurn() >=2){
      commands.push_back(std::make_shared<CommandNextEntity>());
    }
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
