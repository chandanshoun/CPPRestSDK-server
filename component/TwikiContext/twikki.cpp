   #include "twikki.h"
   #include "TwikkiRequest.h"
   #include "IQuery.h"
   #include "twikkiquery.h"
   #include "stdafx.h"

   IModel *Twikki::instance=NULL;


   IModel *Twikki::getInstance()
   {
      if(instance==NULL)
        instance=new Twikki();
      return instance; 
   }

   Twikki::Twikki():mQuery("SELECT * from employee"){}
   Twikki::~Twikki(){}

   void Twikki::BuildfromDB()
   {
    try
    {
      //Prepare statement
      auto_ptr<sql::PreparedStatement> prep_stmt;
      prep_stmt.reset(DBHandler::getDBInstance()->getDBConnection()->prepareStatement(mQuery.c_str()));
      shared_ptr<sql::ResultSet> res;
      res.reset(prep_stmt->executeQuery());

      while (res->next())
      {
         std::string key=res->getString("Name");
         key.append(res->getString("Month"));
         std::string taskKey=res->getString("Category");
         {
           std::unique_lock<std::mutex> mlock(locks);
           taskList[key].insert({taskKey,new Task(res->getInt("id"), res->getString("Task"), res->getInt("efforts"))}); 
         }
      }
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

   void  Twikki::Insert(std::shared_ptr<IQuery> singleQuery)
   { 
      std::string key=std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->name;
      key.append(std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->month);
      std::string taskKey=std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->category;
      {
        std::unique_lock<std::mutex> mlock(locks);
        taskList[key].insert({taskKey,new Task(std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->id, std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->task, std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->efforts)});
      }
   }

   void  Twikki::Delete(std::shared_ptr<TableRow> row)
   {
      std::string key=row->getName();
      key.append(row->getMonth());
      std::cout<<" delete called with key "<<key<<endl;
      {
      std::unique_lock<std::mutex> mlock(locks);
      auto innerItr=taskList[key].begin();
      while(innerItr!=taskList[key].end())
      {
         if(innerItr->second->getID()==row->getID())
         {
            delete(innerItr->second);
            taskList[key].erase(innerItr);
         }
         innerItr++;
      }
     }
   }

   void  Twikki::Update(std::shared_ptr<IQuery> singleQuery)
   {
      std::string key=std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->name;
      key.append(std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->month);
      std::string taskKey=std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->category;
      {
      std::unique_lock<std::mutex> mlock(locks);
      auto innerItr=taskList[key].find(taskKey);
      auto last=taskList[key].upper_bound(taskKey);
      while(innerItr!=last)
      {
         if(innerItr->second->getID()==std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->id)
         {
           innerItr->second->setTask(std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->task);
           innerItr->second->setEfforts(std::dynamic_pointer_cast<TwikkiQuery>(singleQuery)->efforts);
           break;
         }
         innerItr++;
      }
     } 
   }

   void  Twikki::Query(std::shared_ptr<IRequest> req)
   {
    cout<<" key is "<<req->mkey<<endl;
    std::string subkey=req->mkey.substr(0,req->mkey.size()-3);
    std::string month=req->mkey.substr(req->mkey.size()-3,req->mkey.size());
    std::unique_lock<std::mutex> mlock(locks);
    if(subkey=="All")
    {
     for(auto mainItr=taskList.begin();mainItr!=taskList.end();mainItr++)
     {
       cout<<" key is "<<mainItr->first<<","<<month<<endl;
       if(mainItr->first.substr(mainItr->first.size()-3,mainItr->first.size())==month)
       { 
         auto itr=taskList[mainItr->first].begin();
         while(itr!=taskList[mainItr->first].end())
         {
            std::string category=itr->first;
            int effort=0;
            //itr=taskList[mainItr->first].find(itr->first);
            auto last=taskList[mainItr->first].upper_bound(itr->first);
            while(itr!=last)
            {
              effort+=itr->second->getEfforts();
              itr++;
            }
            cout<<category<<" "<<effort<<endl;
            std::dynamic_pointer_cast<TwikkiRequest>(req)->setEfforts(category, effort); 
          }
        }
      }
    }
    else
    {
       cout<<"key is "<<req->mkey<<endl;
       auto itr=taskList[req->mkey].begin();
       while(itr!=taskList[req->mkey].end())
       {
          cout<<itr->first<<" "<<itr->second->getTask()<<" "<<itr->second->getEfforts()<<endl;
          std::dynamic_pointer_cast<TwikkiRequest>(req)->setEfforts(itr->first, itr->second->getEfforts()); 
          itr++;
       }
    }
    auto tempMap=std::dynamic_pointer_cast<TwikkiRequest>(req)->getEfforts(); 
    for(auto itr=tempMap->begin();itr!=tempMap->end();itr++)
      cout<<itr->first<<"value is "<<itr->second<<endl;
   }


