#include "dbupdate.h"
#include "tablerow.h"
#include "genericupdate.h"
#define SELECT_FROM_DBSERVER "SELECT * from update_server"
#define DELETE_FROM_DBSERVER "DELETE FROM update_server where id=? AND tableName=? AND action=?"

DBUpdateThread* DBUpdateThread:: dbInstance=NULL;

using namespace TwikkiContext;

void DBUpdateThread::start()
{
   std::thread* dbThread=new std::thread(&DBUpdateThread::Run,this);
   threadId=dbThread;
}

DBUpdateThread::DBUpdateThread()
{

}

DBUpdateThread::~DBUpdateThread()
{
  threadId->join();
}

void DBUpdateThread::deleteQuery(int id, string tableName, string action)
{
  try
  {
     //Prepare statement
     auto_ptr<sql::PreparedStatement> prep_stmt;
     prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(DELETE_FROM_DBSERVER));
     prep_stmt->setInt(1, id);
     prep_stmt->setString(2, tableName);
     prep_stmt->setString(3, action);
     cout << " delete called "<<endl;
     prep_stmt->execute();
  }
  catch (sql::SQLException &e)
  {
     cout << "# ERR: SQLException in " << __FILE__;
     cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
     cout << "# ERR: " << e.what();
     cout << " (MySQL error code: " << e.getErrorCode();
     cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
  }
}

void DBUpdateThread::updateDB()
{
    try
    {
      //Prepare statement
      auto_ptr<sql::PreparedStatement> prep_stmt;
      prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(SELECT_FROM_DBSERVER));
      shared_ptr<sql::ResultSet> res;
      res.reset(prep_stmt->executeQuery());

      while (res->next())
      {
         // You can use either numeric offsets...
         //cout << "name = " << res->getString("name"); // getInt(1) returns the first column
         //cout << "table name = " << res->getString("tableName"); // getInt(1) returns the first column
         //cout << "Task = " << res->getString("Task"); // getInt(1) returns the first column
         //cout << "action = " << res->getString("action"); // getInt(1) returns the first column
         shared_ptr<TableRow> row(new TableRow());
         row->setID(res->getInt("id"));
         row->setTableName(res->getString("tableName"));
         row->setAction(res->getString("action"));
         row->setName(res->getString("Name"));
         row->setMonth(res->getString("Month"));
         deleteQuery(res->getInt("id"),res->getString("tableName"),res->getString("action"));
         TwikkiManager::getInstance()->Update(row); 
      }
      cout<<endl;
    }
    catch (sql::SQLException &e)
    {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    }
}

void DBUpdateThread::Run()
{
   std::cout<<"DBUpdateThread running now"<<std::endl;
   bool isDBInitailzed=false;
   TwikkiManager::getInstance();
   while(true)
   {
      if(!isDBInitailzed)
      {
         TwikkiManager::getInstance()->updateAllTables();
         isDBInitailzed=true;
      }
      updateDB();
      std::this_thread::sleep_for(std::chrono::seconds(100));     
   } 
} 


