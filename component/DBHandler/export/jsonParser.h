#ifndef _JSONPARSER_H
#define _JSONPARSER_H
#include "jsonpacket.h"
#include<string>

class JsonParser
{
   private:
   JsonPacket *mJPacket;
   std::string mtableName;
   std::string mreqType;

   public:
   JsonParser();
   ~JsonParser();
   bool parseJsonRequest(http_request);
   JsonPacket* getJsonPacket();
   std::string getTableName();
   std::string getRequestType(){ 
      auto const & jvalue = mJPacket->getJsonRequest();
      mreqType=jvalue.at("reqType").as_string();
      return mreqType;
   }
};

#endif
