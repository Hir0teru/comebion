/**
 * @file SeedService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "SeedService.hpp"

SeedService::SeedService () : AbstractService("/seed") {

}

HttpStatus SeedService::get (Json::Value& jsonOut, int id) const {
  jsonOut["seed"] = seed;
  return HttpStatus::OK;
}
HttpStatus SeedService::put (Json::Value& JsonOut, const Json::Value& JsonIn) {
  if (seed == -1)
    seed = JsonIn["seed"].asInt();
  JsonOut["seed"] = seed;
  return HttpStatus::CREATED;
}
