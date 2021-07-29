#include "dbhandler.h"

DBHandler* DBHandler::dbInstance=NULL;
std::mutex DBHandler::locks;

DBHandler::DBHandler()
{
  sql::ConnectOptionsMap connection_properties;
  connection_properties["hostName"] = "tcp://127.0.0.1";
  connection_properties["userName"] = "root";
  connection_properties["password"] = "password";
  connection_properties["schema"] = "employeedb";
  connection_properties["port"] = 3306;
  connection_properties["OPT_RECONNECT"] = true;
  driver = sql::mysql::get_driver_instance();
  shared_ptr<sql::Connection> con(driver->connect(connection_properties));
  mcon=con;
}

DBHandler::~DBHandler()
{
  dbInstance=NULL;
}

DBHandler* DBHandler::getDBInstance()
{
   if(dbInstance==NULL)
   {
     std::unique_lock<std::mutex> mlock(locks);
     if(dbInstance==NULL)
       dbInstance=new DBHandler();
   }
   return dbInstance;  
}
