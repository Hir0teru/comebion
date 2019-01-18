#include "Moteur.h"
#include "engine.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>
#include <microhttpd.h>


#include <cstdlib>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <sys/types.h>

#include "networkManager.h"


using namespace engine;
using namespace networkManager;

// Operations

Moteur::Moteur (){

}
Moteur::Moteur (std::shared_ptr<state::GameState>& gameState, bool record, bool network) : record(record), network(network){
  this -> gameState = gameState;
  author = 0;
}
Moteur::Moteur (std::shared_ptr<state::GameState>& gameState, bool record) : record(record){
  this -> gameState = gameState;
  author = 0;
}
Moteur::Moteur (std::shared_ptr<state::GameState>& gameState) : record(false){
  this -> gameState = gameState;
  author = 0;
}

Moteur::~Moteur (){
  //std::cout << "destroy..." << std::endl;
  if(record){
    std::cout << "record" << std::endl;
    std::ofstream out ("replay.txt", std::ofstream::out);
    out << outputval;
    out.close();
  }
}

void Moteur::AddCommand (std::shared_ptr<Command> command){
  commands.push_back(command);
}
void Moteur::Update (){
  if(!commands.empty()){
    Json::Value jsonToSend;
    int floorNb =  gameState -> GetMap() -> GetCurrentFloor();
    int entityTurn = gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom() -> GetEntityTurn();
    try{
      commands[0] -> Execute(gameState);
      if(record){
        outputval.append(commands[0]->Serialize());
      }
      if(network){
        //jsonToSend.append(commands[0]->Serialize());
        jsonToSend = commands[0]->Serialize();
      }
      commands.erase(commands.begin());
    }
    catch(std::invalid_argument e){
      std::cout << "wrong command: " << e.what() << std::endl;
      commands.erase(commands.begin());
    }
    if (!jsonToSend.empty() && network){
      NetworkManager* NM = NetworkManager::instance();
      if(entityTurn == author){
        jsonToSend["author"] = author;
        NM->Put ("/command", jsonToSend);
      }
    }
  } else{ // an ennemy is playing -> need to move to next entity
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


std::vector<std::shared_ptr<Command>> Moteur::GetCommands (){
  return commands;
}
void Moteur::SetCommands (std::vector<std::shared_ptr<Command>> commands){
  this -> commands = commands;
}


void Moteur::ReadCommand (Json::Value jsonval){
//std::cout << "read commands" << std::endl;
// reading commands -> need to know the type of the command to deserialize first
for(unsigned int i = 0; i < jsonval.size(); i++){
  std::shared_ptr<Command> cmd;
  std::string typeCmd = jsonval[i]["typeCmd"].asString();
  std::cout << "type is: " <<typeCmd << std::endl;
  if(typeCmd.compare("AddBlock") == 0){
    cmd = std::shared_ptr<CommandAddBlock>((new CommandAddBlock()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("AddBuff") == 0){
    cmd = std::shared_ptr<CommandAddBuff>((new CommandAddBuff()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("AddCard") == 0){
    cmd = std::shared_ptr<CommandAddCard>((new CommandAddCard()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("AddDebuff") == 0){
    cmd = std::shared_ptr<CommandAddDebuff>((new CommandAddDebuff()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("AddEnergy") == 0){
    cmd = std::shared_ptr<CommandAddEnergy>((new CommandAddEnergy()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Attack") == 0){
    cmd = std::shared_ptr<CommandAttack>((new CommandAttack()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ChangeElement") == 0){
    cmd = std::shared_ptr<CommandChangeElement>((new CommandChangeElement()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ChangeFloor") == 0){
    cmd = std::shared_ptr<CommandChangeFloor>((new CommandChangeFloor()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("changeIntent") == 0){
    cmd = std::shared_ptr<CommandChangeIntent>((new CommandChangeIntent()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ChangeReward") == 0){
    cmd = std::shared_ptr<CommandChangeReward>((new CommandChangeReward()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ChangeRoom") == 0){
    cmd = std::shared_ptr<CommandChangeRoom>((new CommandChangeRoom()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ChangeStat") == 0){
    cmd = std::shared_ptr<CommandChangeStat>((new CommandChangeStat()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Die") == 0){
    cmd = std::shared_ptr<CommandDie>((new CommandDie()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Discard") == 0){
    cmd = std::shared_ptr<CommandDiscard>((new CommandDiscard()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Draw") == 0){
    cmd = std::shared_ptr<CommandDraw>((new CommandDraw()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("EndFight") == 0){
    cmd = std::shared_ptr<CommandEndFight>((new CommandEndFight()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("EnterRoom") == 0){
    cmd = std::shared_ptr<CommandEnterRoom>((new CommandEnterRoom()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("ExitRoom") == 0){
    cmd = std::shared_ptr<CommandExitRoom>((new CommandExitRoom()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("GameWon") == 0){
    cmd = std::shared_ptr<CommandGameWon>((new CommandGameWon()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Heal") == 0){
    cmd = std::shared_ptr<CommandHeal>((new CommandHeal()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("NewTurn") == 0){
    cmd = std::shared_ptr<CommandNewTurn>((new CommandNewTurn()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("NextEntity") == 0){
    cmd = std::shared_ptr<CommandNextEntity>((new CommandNextEntity()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("PlayCard") == 0){
    cmd = std::shared_ptr<CommandPlayCard>((new CommandPlayCard()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("PlaySkill") == 0){
    cmd = std::shared_ptr<CommandPlaySkill>((new CommandPlaySkill()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("RemoveCard") == 0){
    cmd = std::shared_ptr<CommandRemoveCard>((new CommandRemoveCard()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("Shuffle") == 0){
    cmd = std::shared_ptr<CommandShuffle>((new CommandShuffle()) -> Deserialize(jsonval[i]));
  } else if(typeCmd.compare("UseEnergy") == 0){
    cmd = std::shared_ptr<CommandUseEnergy>((new CommandUseEnergy()) -> Deserialize(jsonval[i]));
  }
  // std::cout<< "Execute command: " << cmd->Serialize().toStyledString() << std::endl;
  // cmd->Execute(gameState);
  // sleep(0.3);
  commands.push_back(cmd);
}

}

bool Moteur::GetRecord(){
  return record;
}

void Moteur::SetRecord(bool record){
  this->record = record;
}

void Moteur::AddJsonValue(Json::Value val){
  outputval.append(val);
}

void Moteur::SetAuthor(int author){
  this->author = author;
}

int Moteur::GetAuthor(){
  return author;
}

bool Moteur::GetNetwork(){
  return network;
}
