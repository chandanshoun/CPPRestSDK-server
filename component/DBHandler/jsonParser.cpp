#include "jsonParser.h"
#include<iostream>
using namespace std;

JsonParser::JsonParser()
{
  mJPacket=NULL;
}

JsonParser::~JsonParser()
{
  if(mJPacket)
    delete mJPacket;
  mJPacket=NULL;
}

bool JsonParser::parseJsonRequest(http_request request)
{
   std::cout<<"chandan Parse "<<request.to_string()<<std::endl;
   request
      .extract_json()
      .then([request, this](pplx::task<json::value> task) {
         try
         {
          auto const jvalue = task.get();
          mJPacket = new JsonPacket(jvalue);
          mtableName=jvalue.at("tableName").as_string();
          return true;
         }
         catch (http_exception const & e)
         {
            cout << e.what() << endl;
            return false;
         }
      }).wait();
      return true;
}

JsonPacket* JsonParser::getJsonPacket()
{
    return mJPacket;
}

std::string JsonParser::getTableName()
{
    return mtableName;
}

