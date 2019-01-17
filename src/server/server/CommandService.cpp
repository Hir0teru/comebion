/**
 * @file CommandService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "CommandService.hpp"
#include <iostream>

CommandService::CommandService (CommandDB& commandDB) : AbstractService("/command"),
commandDB(commandDB)
 {

}

HttpStatus CommandService::get (Json::Value& out, int id) const {
  // if (id == 0){
  //   const Cmd* command = commandDB.getCommand(id);
  //   if (!command)
  //       throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
  //   out["typeCmd"] = command->typeCmd;
  //   out["entityID"] = command->entityID;
  //   out["block"] = command->block;
  //   out["target"] = command->target;
  //   out["buff_AP"] = command->buff_AP;
  //   out["buff_BP"] = command->buff_BP;
  //   out["buff_E"] = command->buff_E;
  //   out["buff_H"] = command->buff_H;
  //   out["playerID"] = command->playerID;
  //   out["card"] = command->card;
  //   out["isDeckFull"] = command->isDeckFull;
  //   out["debuff_AM"] = command->debuff_AM;
  //   out["debuff_BM"] = command->debuff_BM;
  //   out["energyAmount"] = command->energyAmount;
  //   out["damage"] = command->damage;
  //   out["entityLife"] = command->entityLife;
  //   out["targetLife"] = command->targetLife;
  //   out["element"] = command->element;
  //   out["previousElement"] = command->previousElement;
  //   out["statAttack"] = command->statAttack;
  //   out["statBlock"] = command->statBlock;
  //   out["previousStatAttack"] = command->previousStatAttack;
  //   out["previousStatBlock"] = command->previousStatBlock;
  //   out["cardID"] = command->cardID;
  //   out["isFightWon"] = command->isFightWon;
  //   out["heal"] = command->heal;
  //   out["targetID"] = command->targetID;
  //   out["cardIndex"] = command->cardIndex;
  //   out["enemyID"] = command->enemyID;
  //   out["skillIndex"] = command->skillIndex;
  //   out["index"] = command->index;
  // } else {
  std::vector<unique_ptr<Cmd>>& commands = commandDB.getCommands(id);
  if(!commands.empty()){
    for (size_t i = 0; i < commands.size(); i ++) {
      Json::Value val;
      val["typeCmd"] = commands[i]->typeCmd;
      val["entityID"] = commands[i]->entityID;
      val["block"] = commands[i]->block;
      val["target"] = commands[i]->target;
      val["buff_AP"] = commands[i]->buff_AP;
      val["buff_BP"] = commands[i]->buff_BP;
      val["buff_E"] = commands[i]->buff_E;
      val["buff_H"] = commands[i]->buff_H;
      val["playerID"] = commands[i]->playerID;
      val["card"] = commands[i]->card;
      val["isDeckFull"] = commands[i]->isDeckFull;
      val["debuff_AM"] = commands[i]->debuff_AM;
      val["debuff_BM"] = commands[i]->debuff_BM;
      val["energyAmount"] = commands[i]->energyAmount;
      val["damage"] = commands[i]->damage;
      val["entityLife"] = commands[i]->entityLife;
      val["targetLife"] = commands[i]->targetLife;
      val["element"] = commands[i]->element;
      val["previousElement"] = commands[i]->previousElement;
      val["statAttack"] = commands[i]->statAttack;
      val["statBlock"] = commands[i]->statBlock;
      val["previousStatAttack"] = commands[i]->previousStatAttack;
      val["previousStatBlock"] = commands[i]->previousStatBlock;
      val["cardID"] = commands[i]->cardID;
      val["isFightWon"] = commands[i]->isFightWon;
      val["heal"] = commands[i]->heal;
      val["targetID"] = commands[i]->targetID;
      val["cardIndex"] = commands[i]->cardIndex;
      val["enemyID"] = commands[i]->enemyID;
      val["skillIndex"] = commands[i]->skillIndex;
      val["index"] = commands[i]->index;
      out.append(val);
    }
  }

  return HttpStatus::OK;
}

HttpStatus CommandService::post (const Json::Value& in, int id) {
  std::cout << "post isn't implemented" << std::endl;
  // const Cmd* command = commandDB.getCommand(id);
  // if (!command)
  //     throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
  // unique_ptr<Cmd> commandmod (new Cmd(*command));
  // if (in.isMember("entityID")) {
  //     commandmod->entityID = in["entityID"].asInt();
  // }
  // if (in.isMember("block")) {
  //     commandmod->block = in["block"].asInt();
  // }
  // commandDB.setCommand(id,std::move(commandmod));
  return HttpStatus::NO_CONTENT;
}

HttpStatus CommandService::put (Json::Value& out, const Json::Value& in) {
  std::string typeCmd = "";
  int entityID = 0, block = 0, target = 0, buff_AP = 0, buff_BP = 0, buff_E = 0, buff_H = 0, buff_R = 0, playerID = 0, card = 0, author = -1;
  bool isDeckFull = false, isFightWon = false;
  int debuff_AM = 0, debuff_BM = 0, energyAmount = 0, damage = 0, entityLife = 0, targetLife = 0, element = 0;
  int previousElement = 0, intent = 0, previousIntent = 0, statAttack = 0, statBlock = 0, previousStatAttack = 0, previousStatBlock = 0;
  int cardID = 0, heal = 0, targetID = 0, cardIndex = 0, enemyID = 0,skillIndex = 0, index = 0;
  if(in.isMember("author")){
    author = in["author"].asInt();
  }
  if(in.isMember("typeCmd")){
    typeCmd = in["typeCmd"].asString();
  }
  if(in.isMember("entityID")){
    entityID = in["entityID"].asInt();
  }
  if(in.isMember("block")){
    block = in["block"].asInt();
  }
  if(in.isMember("target")){
    target = in["target"].asInt();
  }
  if(in.isMember("buff_AP")){
    buff_AP = in["buff_AP"].asInt();
  }
  if(in.isMember("buff_BP")){
    buff_BP = in["buff_BP"].asInt();
  }
  if(in.isMember("buff_E")){
    buff_E = in["buff_E"].asInt();
  }
  if(in.isMember("buff_H")){
    buff_H = in["buff_H"].asInt();
  }
  if(in.isMember("playerID")){
    playerID = in["playerID"].asInt();
  }
  if(in.isMember("card")){
    card = in["card"].asInt();
  }
  if(in.isMember("isDeckFull")){
    isDeckFull = in["isDeckFull"].asBool();
  }
  if(in.isMember("debuff_AM")){
    debuff_AM = in["debuff_AM"].asInt();
  }
  if(in.isMember("debuff_BM")){
    debuff_BM = in["debuff_BM"].asInt();
  }
  if(in.isMember("energyAmount")){
    energyAmount = in["energyAmount"].asInt();
  }
  if(in.isMember("damage")){
    damage = in["damage"].asInt();
  }
  if(in.isMember("entityLife")){
    entityLife = in["entityLife"].asInt();
  }
  if(in.isMember("targetLife")){
    targetLife = in["targetLife"].asInt();
  }
  if(in.isMember("element")){
    element = in["element"].asInt();
  }
  if(in.isMember("previousElement")){
    previousElement = in["previousElement"].asInt();
  }
  if(in.isMember("intent")){
    intent = in["intent"].asInt();
  }
  if(in.isMember("previousIntent")){
    previousIntent = in["previousIntent"].asInt();
  }

  if(in.isMember("statAttack")){
    statAttack = in["statAttack"].asInt();
  }
  if(in.isMember("statBlock")){
    statBlock = in["statBlock"].asInt();
  }
  if(in.isMember("previousStatAttack")){
    previousStatAttack = in["previousStatAttack"].asInt();
  }
  if(in.isMember("previousStatBlock")){
    previousStatBlock = in["previousStatBlock"].asInt();
  }
  if(in.isMember("cardID")){
    cardID = in["cardID"].asInt();
  }
  if(in.isMember("isFightWon")){
    isFightWon = in["isFightWon"].asBool();
  }
  if(in.isMember("heal")){
    heal = in["heal"].asInt();
  }
  if(in.isMember("targetID")){
    targetID = in["targetID"].asInt();
  }
  if(in.isMember("cardIndex")){
    cardIndex = in["cardIndex"].asInt();
  }
  if(in.isMember("enemyID")){
    enemyID = in["enemyID"].asInt();
  }
  if(in.isMember("skillIndex")){
    skillIndex = in["skillIndex"].asInt();
  }
  if(in.isMember("index")){
    index = in["index"].asInt();
  }

  out = commandDB.addCommand(std::make_unique<Cmd>(author,
    typeCmd,
    entityID,
    block,
    target,
    buff_AP,
    buff_BP,
    buff_E,
    buff_R,
    buff_H,
    playerID,
    card,
    isDeckFull,
    debuff_AM,
   debuff_BM,
   energyAmount,
   damage,
   entityLife,
   targetLife,
   element,
   previousElement,
   intent,
   previousIntent,
   statAttack,
   statBlock,
   previousStatAttack,
   previousStatBlock,
   cardID,
   isFightWon,
   heal,
   targetID,
   cardIndex,
   enemyID,
   skillIndex,
   index));
  return HttpStatus::CREATED;
}

HttpStatus CommandService::remove (int id) {
  // const Cmd* command = commandDB.getCommand(id);
  // if (!command)
  //     throw ServiceException(HttpStatus::NOT_FOUND,"Invalid Command id");
  // commandDB.removeCommand(id);
  commandDB.removeCommands(id);
  return HttpStatus::NO_CONTENT;
}
