#ifndef __TWIKKIMANAGER__H
#define __TWIKKIMANAGER__H
#include "genericupdate.h"
#include "Itable.h"
#include "IModel.h"
#include "twikki.h"
#include "twikkiquery.h"
#include "tablerow.h"
#include <string>
#include <map>
#include <memory>
#include <mutex>
using namespace std;
#include "IRequest.h"

namespace TwikkiContext
{

class TwikkiManager 
{
   private:
   std::map<std::string,ITable *> mTable;   
   std::map<std::string,IModel *> iTable;   
   static TwikkiManager* twikkiInstance;
   GenericUpdate<Twikki, TwikkiQuery> mTwikki;
   static std::mutex locks;

   public:
   TwikkiManager();
   ~TwikkiManager();
   void updateAllTables(); 
   void AddTable(std::string);
   void Query(std::shared_ptr<IRequest>);
   void Update(shared_ptr<TableRow> row);
   void Register(std::string, ITable &);
   static TwikkiManager* getInstance()
   {
      if(twikkiInstance==NULL)
      {
        std::unique_lock<std::mutex> mlock(locks);
         if(twikkiInstance==NULL)
           twikkiInstance=new TwikkiManager();
      }
      return twikkiInstance;
   }
};

}

#endif
