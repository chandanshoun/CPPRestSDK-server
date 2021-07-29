#ifndef __TWIKKI__H
#define __TWIKKI__H
#include "IModel.h"
#include "IQuery.h"
#include<map>
#include<mutex>

class Twikki :public IModel
{
   private:
   class Task
   {
     private:
       int mid;
       std::string mTask;
       int mefforts;

     public:
       Task(int id, std::string tName, int efforts):mid(id), mTask(tName), mefforts(efforts)
       {

       }
       int getID(){return mid;}
       void setID(int id){mid=id;}
       std::string getTask(){return mTask;}
       void setTask(std::string task){mTask=task;}
       int getEfforts(){return mefforts;}
       void setEfforts(int effort){mefforts=effort;}
       ~Task()
       {

       }
   };
   std::mutex locks;
   std::string mQuery;
   static IModel *instance;
   std::map<std::string, std::multimap<std::string, Task*>> taskList;

   public:

   static IModel * getInstance();
   Twikki();
   virtual ~Twikki();
   void BuildfromDB();
   void Insert(std::shared_ptr<IQuery>);
   void Delete(std::shared_ptr<TableRow>);
   void Update(std::shared_ptr<IQuery>);
   void Query(std::shared_ptr<IRequest>);
};

#endif
