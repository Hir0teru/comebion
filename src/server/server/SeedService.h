#ifndef SEEDSERVICE__H
#define SEEDSERVICE__H

#include "HttpStatus.h"
#include "AbstractService.h"

/// class SeedService -
class SeedService : public AbstractService {
  // Operations
private:
  int seed = -1;

public:
  SeedService ();
  HttpStatus get (Json::Value& out, int id) const;
  HttpStatus put (Json::Value& out, const Json::Value& in);
};

#endif
