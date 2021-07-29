#ifndef _JSONRESPONSE_H
#define _JSONRESPONSE_H
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <iostream>
#include <vector>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;


class JsonResponse
{
  private:
  //Doing this for Deep copy.
  json::value jsonResponse;  
  std::vector<json::value> arrayResponse;

  public:
  ~JsonResponse(){} 
  void setJsonResponse(std::string key, std::string value){jsonResponse[key]=json::value::string(value);}
  void setJsonResponseInt(std::string key, int value){jsonResponse[key]=json::value::number(value);}
  void setJsonResponseArray(json::value &obj, std::string key, std::string value)
  {
    obj[key]=json::value::string(value);  
  }
  void setJsonResponseArrayInt(json::value &obj, std::string key, int value)
  {
    obj[key]=json::value::number(value);  
  }
  void appendJsonResponseArray(json::value obj){arrayResponse.push_back(obj);}
  void finalizeResponseArray(std::string key){jsonResponse[key]=json::value::array(arrayResponse);}
  const json::value &getJsonResponse(){return std::move(jsonResponse);}
};

#endif
