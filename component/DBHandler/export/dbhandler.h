#ifndef _DBHANDLER_H
#define _DBHANDLER_H
#include<map>
#include<string>
#include<mutex>
#include "ctable.h"
#include "employee.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <iostream>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace sql;
using namespace std;
using namespace sql::mysql;

class DBHandler
{
  private:
  static DBHandler *dbInstance;
  sql::ConnectOptionsMap connection_properties;
  sql::mysql::MySQL_Driver *driver;
  shared_ptr<sql::Connection> mcon;
  static std::mutex locks;

  public:
   CTable *getTableInstance(std::string str);
   DBHandler();
   virtual ~DBHandler();   
   static DBHandler *getDBInstance();
   shared_ptr<sql::Connection> getDBConnection(){return mcon;}

};

#endif
