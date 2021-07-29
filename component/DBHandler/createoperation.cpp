#include "createoperation.h"
#include <memory>
#include <iostream>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace std;

CreateOperation::CreateOperation()
{
}

CreateOperation::CreateOperation(http_request &req):mrequest(req)
{
}

CreateOperation::~CreateOperation()
{

}


void CreateOperation::execute()
{
 std::cout<<"execute called"<<std::endl; 
 auto_ptr<JsonParser> parser(new JsonParser());
 shared_ptr<CTable> table(nullptr);
 if(parser->parseJsonRequest(mrequest))
 {
    bool status=false;
    JsonPacket *reqpacket=parser->getJsonPacket();
    string tableName=parser->getTableName();
    if(tableName.compare("employee")==0)
    {
      cout<<"employee found "<<endl; 
      shared_ptr<CTable> newtable(new Employee(new JsonResponse()));
      table=newtable;
    }
    if(table->ParseTableData(reqpacket))
      status=table->Insert();

    if(status)
    {
      JsonResponse *response = table->getJsonResponse();
      auto answer=response->getJsonResponse();
      mrequest.reply(status_codes::OK, answer);
    }
    else
    {
       std::cout<<"data insert failed"<<std::endl; 
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
