#include "twikkiquery.h"
#include "stdafx.h"

void TwikkiQuery::BuildQuery(std::shared_ptr<TableRow> row)
{
  try
  {
     //Prepare statement
     tname=row->getTableName();
     prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(mQuery.c_str()));
     prep_stmt->setInt(1, row->getID());
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

void TwikkiQuery::executeQuery()
{
    try
    {
      shared_ptr<sql::ResultSet> res;
      res.reset(prep_stmt->executeQuery());

      while (res->next())
      {
         // You can use either numeric offsets...
         cout << "id = " << res->getInt("id"); // getInt(1) returns the first column
         cout << "name = " << res->getString("Name"); // getInt(1) returns the first column
         cout << "month = " << res->getString("Month"); // getInt(1) returns the first column
         cout << "Task = " << res->getString("Task"); // getInt(1) returns the first column
         id=res->getInt("id");
         name=res->getString("Name");
         month=res->getString("Month");
         task=res->getString("Task");
         category=res->getString("Category"); 
         efforts=res->getInt("Efforts"); 
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
