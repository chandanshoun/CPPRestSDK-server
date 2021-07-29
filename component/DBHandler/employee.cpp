#include "employee.h"
#include<iostream>
#define INSERT_INTO_EMPLOYEE "INSERT INTO employee ( Name, Month, Category, Task, Efforts ) VALUES ( ?, ?, ?, ?, ?)"
#define SELECT_FROM_EMPLOYEE "SELECT * FROM employee where name=? AND month=?"
#define DELETE_FROM_EMPLOYEE "DELETE FROM employee where name=? AND task=?"
#define UPDATE_IN_EMPLOYEE "UPDATE employee SET Efforts=? WHERE Name=? AND Task=?"

using namespace std;

Employee::Employee():name("dummy"),month("dummy")
{

}

Employee::~Employee()
{


}

bool Employee::Insert()
{
  try
  {
    //Prepare statement
    auto_ptr<sql::PreparedStatement> prep_stmt;
    prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(INSERT_INTO_EMPLOYEE));
    prep_stmt->setString(1, name);
    prep_stmt->setString(2, month);
    prep_stmt->setString(3, category);
    prep_stmt->setString(4, task);
    prep_stmt->setInt(5, efforts);
    prep_stmt->execute();
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("name",name);
    response->setJsonResponse("month",month);
    response->setJsonResponse("category",category);
    response->setJsonResponse("task",task);
    response->setJsonResponseInt("efforts",efforts);
    return true;
  }
  catch (sql::SQLException &e)
  {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("error",e.what());
    return false;
  }
}

bool Employee::ParseTableData(JsonPacket *packet)
{
      try
      { 
         auto const & jvalue = packet->getJsonRequest();
         auto array = jvalue.at("tableRecords").as_array();
         name = array[0].at("name").as_string();
         month= array[0].at("month").as_string();
         category= array[0].at("category").as_string();
         task= array[0].at("taskName").as_string();
         string effort= array[0].at("efforts").as_string();
         efforts=stoi(effort); 
         cout<<" name : "<<name<<"month:"<<month<<category<<task<<efforts<<endl;
         return true;
      }
      catch (http_exception const & e)
      {
         cout << e.what() << endl;
         JsonResponse *response=getJsonResponse();
         response->setJsonResponse("error",e.what());
         return false;
      }
      return true;
}

bool Employee::ParseTableDataUpdate(JsonPacket *packet)
{
      try
      {
         auto const & jvalue = packet->getJsonRequest();
         auto array = jvalue.at("tableRecords").as_array();
         name = array[0].at("name").as_string();
         month= array[0].at("month").as_string();
         category= array[0].at("category").as_string();
         task= array[0].at("taskName").as_string();
         string effort= array[0].at("efforts").as_string();
         efforts=stoi(effort);
         cout<<"Update name : "<<name<<"month:"<<month<<category<<task<<efforts<<endl;
         return true;
      }
      catch (http_exception const & e)
      {
         cout << e.what() << endl;
         JsonResponse *response=getJsonResponse();
         response->setJsonResponse("error",e.what());
         return false;
      }
      return true;
}

bool Employee::ParseTableDataGet(JsonPacket *packet)
{
      try
      { 
         auto const & jvalue = packet->getJsonRequest();
         auto array = jvalue.at("tableRecords").as_array();
         name = array[0].at("name").as_string();
         month= array[0].at("month").as_string();
         cout<<" name : "<<name<<"month:"<<month<<endl;
         return true;
      }
      catch (http_exception const & e)
      {
         cout << e.what() << endl;
         JsonResponse *response=getJsonResponse();
         response->setJsonResponse("error",e.what());
         return false;
      }
      return true;
}

bool Employee::ParseTableDataDelete(JsonPacket *packet)
{
      try
      {
         auto const & jvalue = packet->getJsonRequest();
         auto array = jvalue.at("tableRecords").as_array();
         name = array[0].at("ename").as_string();
         task = array[0].at("etask").as_string();
         cout<<"name: "<<name<<"task: "<<task<<endl;
         return true;
      }
      catch (http_exception const & e)
      {
         cout << e.what() << endl;
         JsonResponse *response=getJsonResponse();
         response->setJsonResponse("error",e.what());
         return false;
      }
      return true;
}

bool Employee::Delete()
{
  try
  {

    //Prepare statement
    auto_ptr<sql::PreparedStatement> prep_stmt;
    prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(DELETE_FROM_EMPLOYEE));
    prep_stmt->setString(1, name);
    prep_stmt->setString(2, task);
    cout << " delete called "<<name<<task<<endl;
    prep_stmt->execute();
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("name",name);
    response->setJsonResponse("task",task);
    return true;
  }
  catch (sql::SQLException &e)
  {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("error",e.what());
    return false;
  }
  return true;
}


bool Employee::Update()
{
  try
  {
    //Prepare statement
    auto_ptr<sql::PreparedStatement> prep_stmt;
    prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(UPDATE_IN_EMPLOYEE));
    prep_stmt->setInt(1, efforts);
    prep_stmt->setString(2, name);
    prep_stmt->setString(3, task);
    prep_stmt->execute();
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("name",name);
    response->setJsonResponse("month",month);
    response->setJsonResponse("category",category);
    response->setJsonResponse("task",task);
    response->setJsonResponseInt("efforts",efforts);
    return true;
  }
  catch (sql::SQLException &e)
  {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("error",e.what());
    return false;
  }
  return true;
}

bool Employee::Query()
{
  try
  {
    //Prepare statement
    auto_ptr<sql::PreparedStatement> prep_stmt;
    prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(SELECT_FROM_EMPLOYEE));
    prep_stmt->setString(1, name);
    prep_stmt->setString(2, month);
    auto_ptr<sql::ResultSet> res;
    res.reset(prep_stmt->executeQuery());
    JsonResponse *response=getJsonResponse();
    while (res->next()) 
    {
       // You can use either numeric offsets...
       cout << "name = " << res->getString("name"); // getInt(1) returns the first column
       cout << ", month = '" << res->getString("month") << "'" << endl;
       JsonResponse *response=getJsonResponse();
       json::value obj;
       response->setJsonResponseArray(obj,"name", res->getString("name"));
       response->setJsonResponseArray(obj,"month",res->getString("month"));
       response->setJsonResponseArray(obj,"category",res->getString("category"));
       response->setJsonResponseArray(obj,"task",res->getString("task"));
       response->setJsonResponseArrayInt(obj,"efforts",res->getInt("efforts"));
       json::value finalObj=obj; 
       response->appendJsonResponseArray(std::move(finalObj));
    }
    response->finalizeResponseArray("employee");
    return true;
  }
  catch (sql::SQLException &e)
  {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    JsonResponse *response=getJsonResponse();
    response->setJsonResponse("error",e.what());
    return false;
  }
  return true;
}
