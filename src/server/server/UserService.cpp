/**
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"

UserService::UserService (UserDB& userDB) : AbstractService("/user"),
    userDB(userDB) {

}

HttpStatus UserService::get (Json::Value& out, int id) const {
  if (id >= 0){
    const User* user = userDB.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["name"] = user->name;
  } else {
    for (auto it=userDB.getUsers().begin(); it!=userDB.getUsers().end(); ++it) {
      Json::Value val;
      val["name"] = it->second->name;
      out.append(val);
    }
  }

  return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
  const User* user = userDB.getUser(id);
  if (!user)
      throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
  unique_ptr<User> usermod (new User(*user));
  if (in.isMember("name")) {
      usermod->name = in["name"].asInt();
  }
  userDB.setUser(id,std::move(usermod));
  return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out, const Json::Value& in) {
  if (userDB.getUsers().size() <= 1 ){
    int name = in["name"].asInt();
    out["id"] = userDB.addUser(std::make_unique<User>(name));
    return HttpStatus::CREATED;
  } else {
    return HttpStatus::NO_CONTENT;
  }
}

HttpStatus UserService::remove (int id) {
  const User* user = userDB.getUser(id);
  if (!user)
      throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
  userDB.removeUser(id);
  return HttpStatus::NO_CONTENT;
}
