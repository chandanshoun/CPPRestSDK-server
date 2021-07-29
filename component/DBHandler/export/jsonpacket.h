#ifndef _JSONPACKET_H
#define _JSONPACKET_H
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;


class JsonPacket
{
  private:
  //Doing this for Deep copy.
  const json::value jsonRequest;  

  public:
  JsonPacket(const json::value jsonR):jsonRequest(std::move(jsonR)){ }
  ~JsonPacket(){} 
  const json::value &getJsonRequest(){return std::move(jsonRequest);}
};

#endif
