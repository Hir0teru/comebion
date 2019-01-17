/**
 * @file CommandService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "CommandService.hpp"

CommandService::CommandService (CommandDB& commandDB) : AbstractService("/command"),
commandDB(commandDB)
 {

}

HttpStatus CommandService::get (Json::Value& out, int id) const {
  if (id >= 0){
    const Cmd* command = commandDB.getCommand(id);
    if (!command)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
    out["entityID"] = command->entityID;
    out["block"] = command->block;
  } else {
    for (auto it=commandDB.getCommands().begin(); it!=commandDB.getCommands().end(); ++it) {
      Json::Value val;
      val["entityID"] = it->second->entityID;
      val["block"] = it->second->block;
      out.append(val);
    }
  }

  return HttpStatus::OK;
}

HttpStatus CommandService::post (const Json::Value& in, int id) {
  const Cmd* command = commandDB.getCommand(id);
  if (!command)
      throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
  unique_ptr<Cmd> commandmod (new Cmd(*command));
  if (in.isMember("entityID")) {
      commandmod->entityID = in["entityID"].asInt();
  }
  if (in.isMember("block")) {
      commandmod->block = in["block"].asInt();
  }
  commandDB.setCommand(id,std::move(commandmod));
  return HttpStatus::NO_CONTENT;
}

HttpStatus CommandService::put (Json::Value& out, const Json::Value& in) {
  int entityID = in["entityID"].asInt();
  int block = in["block"].asInt();
  out["id"] = commandDB.addCommand(std::make_unique<Cmd>(entityID, block));
  return HttpStatus::CREATED;
}

HttpStatus CommandService::remove (int id) {
  const Cmd* command = commandDB.getCommand(id);
  if (!command)
      throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
  commandDB.removeCommand(id);
  return HttpStatus::NO_CONTENT;
}
