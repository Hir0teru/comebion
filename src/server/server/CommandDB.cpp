/**
 * @file CommandDB.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "CommandDB.hpp"

CommandDB::CommandDB() : idseq(1) {

}

const Cmd* CommandDB::getCommand (int id) const {
    auto ite = commands.find(id);
    if (ite == commands.cend())
        return nullptr;
    return ite->second.get();
}

int CommandDB::addCommand (unique_ptr<Cmd> command) {
    int id = idseq++;
    commands.insert(std::make_pair(id,std::move(command)));
    return id;
}

void CommandDB::setCommand (int id, unique_ptr<Cmd> command) {
    commands[id] = std::move(command);
    if (id > idseq) {
        idseq = id;
    }
}

void CommandDB::removeCommand (int id) {
    auto ite = commands.find(id);
    if (ite == commands.end())
        return;
    commands.erase(ite);
}

map<int,unique_ptr<Cmd> >& CommandDB::getCommands () {
    return commands;
}
