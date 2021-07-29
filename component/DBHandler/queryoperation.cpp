#include "twikkimanager.h"
#include "queryoperation.h"
#include "TwikkiRequest.h"
#include <memory>
#include <iostream>
#include <cpprest/json.h>

QueryOperation::QueryOperation()
{
}

QueryOperation::QueryOperation(http_request &req):mrequest(req)
{
}

QueryOperation::~QueryOperation()
{

}

void QueryOperation::execute()
{
 std::cout<<"execute called for Query"<<std::endl; 
 auto_ptr<JsonParser> parser(new JsonParser());
 shared_ptr<CTable> table(nullptr);
 if(parser->parseJsonRequest(mrequest))
 {
    bool status=false;
    JsonPacket *reqpacket=parser->getJsonPacket();
    string tableName=parser->getTableName();
    string requestType=parser->getRequestType();
    if((tableName.compare("employee")==0)&&(requestType=="Static"))
    {
      cout<<"employee found "<<endl; 
      shared_ptr<CTable> employeetable(new Employee(new JsonResponse()));
      table=employeetable;
    }
    else if((tableName.compare("employee")==0)&&(requestType=="Dynamic"))
    {
      std::string key;
      auto const & jvalue = reqpacket->getJsonRequest();
      auto array = jvalue.at("tableRecords").as_array();
      key = array[0].at("name").as_string();
      key.append(array[0].at("month").as_string());
      std::shared_ptr<IRequest> ireq(std::make_shared<TwikkiRequest>(TwikkiRequest(key,tableName)));
      TwikkiContext::TwikkiManager::getInstance()->Query(ireq);

      //Retrieving Json Response from iReq Map.
      auto response = std::make_shared<JsonResponse>(JsonResponse());
      auto tempMap=std::dynamic_pointer_cast<TwikkiRequest>(ireq)->getEfforts();
      for(auto itr=tempMap->begin();itr!=tempMap->end();itr++)
      {
        json::value obj;
        response->setJsonResponseArray(obj,"category", itr->first);
        response->setJsonResponseArrayInt(obj,"effort",itr->second);
        json::value finalObj=obj;
        response->appendJsonResponseArray(std::move(finalObj));
      }
      response->finalizeResponseArray("employee");
      auto answer=response->getJsonResponse();
      cout<<"answer is "<<answer.serialize(); 
      mrequest.reply(status_codes::OK, answer);
      return;
    }
    else
    {
      cout<<"employee not found "<<endl; 
      return;
    }
    if(table->ParseTableDataGet(reqpacket))
       status=table->Query();

    if(status)
    {
      JsonResponse *response = table->getJsonResponse();
      auto answer=response->getJsonResponse();
      cout<<"answer is "<<answer.serialize(); 
      mrequest.reply(status_codes::OK, answer);
    }
    else
    {
       std::cout<<"Query failed"<<std::endl; 
       JsonResponse *response = table->getJsonResponse();
       auto answer=response->getJsonResponse();
       cout<<"answer is "<<answer.serialize().c_str(); 
       cout<<"answer "<<answer.at("error").as_string()<<endl;
       mrequest.reply(status_codes::OK, answer);
    }
 }
 else
   std::cout<<"Parsing failed"<<std::endl;
}
