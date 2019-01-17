#ifndef CommandSERVICE__H
#define CommandSERVICE__H

#include "HttpStatus.h"
#include "AbstractService.h"
#include "CommandDB.h"

/// class CommandService -
class CommandService : public AbstractService {
  // Associations
  // Attributes
protected:
  CommandDB& commandDB;
  // Operations
public:
  CommandService (CommandDB& commandDB);
  HttpStatus get (Json::Value& out, int id) const;
  HttpStatus post (const Json::Value& in, int id);
  HttpStatus put (Json::Value& out, const Json::Value& in);
  HttpStatus remove (int id);
};

#endif
