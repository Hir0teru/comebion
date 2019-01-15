#include "NetworkManager.h"
#include <microhttpd.h>
#include <iostream>

using namespace networkManager;

NetworkManager* NetworkManager::inst;

NetworkManager::NetworkManager(){
  Json::Value jsonInit;
  Json::Value jsonOut;
  http.setHost(url, port);
  name = rand();
  jsonInit["name"] = name;

  jsonOut = this->Put("/user", jsonInit);
  this->id = jsonOut["id"].asInt();
}

void NetworkManager::InitConnection(){
  http.setHost(url, port);
}

NetworkManager* NetworkManager::instance (){
  if (!inst){
    inst = new NetworkManager();
  }
  return inst;
}

Json::Value NetworkManager::Get (std::string uri){
  // std::cout<<"Connection to server"<<std::endl;

  sf::Http::Request request;
  request.setMethod(sf::Http::Request::Get);
  request.setUri(uri);
  request.setHttpVersion(1, 1); // HTTP 1.1

  sf::Http::Response response = http.sendRequest(request);
  if (response.getStatus() == 200){
    // std::cout<<"GET Successful"<<std::endl;
    Json::Reader jsonReader;
    Json::Value jsonIn;

    if (!jsonReader.parse(response.getBody(),jsonIn))
      throw std::invalid_argument("Json could not be parsed");
    return jsonIn;
    // std::cout<<jsonIn.toStyledString()<<std::endl;
  } else {
    throw std::invalid_argument("GET Failed");
  }
  // std::cout<<"End of connection"<<std::endl;
}

void NetworkManager::Post (std::string uri, Json::Value jsonIn){
  // std::cout<<"Connection to server"<<std::endl;
  sf::Http::Request request;
  request.setMethod(sf::Http::Request::Post);
  request.setUri(uri);
  request.setHttpVersion(1, 1); // HTTP 1.1
  request.setField("From", "me");
  request.setField("Content-Type", "application/x-www-form-urlencoded");
  request.setBody(jsonIn.toStyledString());
  sf::Http::Response response = http.sendRequest(request);
  if (response.getStatus() == 204){
    // std::cout<<"POST Successful"<<std::endl;
  } else {
    throw std::invalid_argument("POST Failed");
  }
  // std::cout<<"End of connection"<<std::endl;
}

Json::Value NetworkManager::Put (std::string uri, Json::Value jsonIn){
  // std::cout<<"Connection to server"<<std::endl;
  sf::Http::Request request;
  request.setMethod(sf::Http::Request::Put);
  request.setUri(uri);
  request.setHttpVersion(1, 1); // HTTP 1.1
  request.setField("From", "me");
  request.setField("Content-Type", "application/x-www-form-urlencoded");
  request.setBody(jsonIn.toStyledString());

  sf::Http::Response response = http.sendRequest(request);
  if (response.getStatus() == 201){
    // std::cout<<"PUT Successful"<<std::endl;
    Json::Reader jsonReader;
    Json::Value jsonOut;

    if (!jsonReader.parse(response.getBody(),jsonOut))
      throw std::invalid_argument("Json could not be parsed");

    // std::cout<<jsonOut.toStyledString()<<std::endl;
    return jsonOut;
  } else {
    throw std::invalid_argument("PUT Failed");
  }
  // std::cout<<"End of connection"<<std::endl;
}

void NetworkManager::Delete (std::string uri){
  // std::cout<<"Connection to server"<<std::endl;
  sf::Http::Request request;
  request.setMethod(sf::Http::Request::Delete);
  request.setUri(uri);
  request.setHttpVersion(1, 1); // HTTP 1.1

  sf::Http::Response response = http.sendRequest(request);
  if (response.getStatus() == 204){
    // std::cout<<"DELETE Successful"<<std::endl;
  } else {
    throw std::invalid_argument("DELETE Failed");
  }
  // std::cout<<"End of connection"<<std::endl;
}

std::string NetworkManager::GetUrl (){
  return url;
}

void NetworkManager::SetUrl (std::string url){
  this->url = url;
  this->InitConnection();
}

int NetworkManager::GetPort (){
  return port;
}

void NetworkManager::SetPort (int port){
  this->port = port;
  this->InitConnection();
}

int NetworkManager::GetId (){
  return id;
}

void NetworkManager::SetId (int id){
  this->id = id;
}

int NetworkManager::GetName (){
  return name;
}

void NetworkManager::SetName (int name){
  this->name = name;
}

NetworkManager::~NetworkManager (){
  this->Delete("/user/"+std::to_string(id));
  std::cout<<"User "<<id<<" deleted"<<std::endl;
}
