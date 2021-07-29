#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

#include "ctable.h"
#include <string>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "dbhandler.h"
#include "jsonpacket.h"
#include <iostream>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "jsonresponse.h"

using namespace sql;
using namespace std;
using namespace sql::mysql;
using namespace web;
using namespace web::http;

class Employee : public CTable
{
   private:
   std::string name;
   std::string month;
   std::string category;
   std::string task;
   int efforts;

   JsonResponse *mresponse;
 
   public:
   Employee();
   Employee(JsonResponse *response):mresponse(response){}
   ~Employee();
   bool ParseTableData(JsonPacket*); 
   bool ParseTableDataGet(JsonPacket*); 
   bool ParseTableDataDelete(JsonPacket*); 
   bool ParseTableDataUpdate(JsonPacket*); 
   bool Insert();
   bool Delete();
   bool Update();
   bool Query();
   JsonResponse *getJsonResponse(){return mresponse;}
};

#endif

