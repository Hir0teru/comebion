/**
 * @file CommandDB.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "CommandDB.hpp"

CommandDB::CommandDB() : idseq(1) {

}

// std::vector<<Cmd*>> CommandDB::getCommand (int id) const {
//     // auto ite = commandsJ1.find(id);
//     // if (ite == commandsJ1.cend())
//     //     return nullptr;
//     // return ite.get
//     return std::vector<Cmd*> truc;
// }

int CommandDB::addCommand (unique_ptr<Cmd> command) {
    //int id = idseq++;
    //commands.insert(std::make_pair(id,std::move(command)));
    int id = command->author;
    if (id == 0){
      commandsJ1.push_back(std::move(command));
    } else if(id == 1){
      commandsJ2.push_back(std::move(command));
    }
    return id;
}

void CommandDB::setCommand (int id, unique_ptr<Cmd> command) {
    // commands[id] = std::move(command);
    // if (id > idseq) {
    //     idseq = id;
    // }
}

void CommandDB::removeCommand (int id) {
    // auto ite = commands.find(id);
    // if (ite == commands.end())
    //     return;
    // commands.erase(ite);
}

std::vector<unique_ptr<Cmd>>& CommandDB::getCommands (int id) {
  if (id == 0){ // J1 : get commandsJ2
    return commandsJ2;
  } else if(id == 1){ //J2 : get commandsJ1
    return commandsJ1;
  } else throw std::invalid_argument("Not a good ID");
}

void CommandDB::removeCommands (int id) {
  if (id == 0){
    commandsJ2.clear();
  } else if(id == 1){
    commandsJ1.clear();
  }

}
