#include "twikkimanager.h"
#include "IModel.h"

namespace TwikkiContext
{

TwikkiManager* TwikkiManager::twikkiInstance=NULL;
std::mutex TwikkiManager::locks;

TwikkiManager::TwikkiManager()
{
    Register("employee",mTwikki);
    AddTable("employee");
}
 
TwikkiManager::~TwikkiManager()
{

}

void TwikkiManager::updateAllTables()
{
  for(auto itr=iTable.begin();itr!=iTable.end();itr++)
  {
     itr->second->BuildfromDB();
  }
}

void TwikkiManager::AddTable(std::string tname)
{
    IModel *interface=IModel::getInstance(tname);
    iTable.insert({tname,interface});
}

void TwikkiManager::Query(std::shared_ptr<IRequest> ireq)
{
    IModel *model=IModel::getInstance(ireq->mtname);
    model->Query(ireq);
}

void TwikkiManager::Update(shared_ptr<TableRow> row)
{
   std::cout<<"Chandan "<<row->getTableName()<<std::endl;   
   auto itr=mTable.find(row->getTableName());
   if(itr!=mTable.end())
   {
     ITable *table=itr->second;

     if(row->getAction()=="insert")
     {
       std::cout<<"insert called"<<std::endl;   
       table->Insert(row);
     }
     if(row->getAction()=="update")
     {
       std::cout<<"update called"<<std::endl;   
       table->Update(row);
     }
     if(row->getAction()=="delete")
     {
       std::cout<<"delete called"<<std::endl;   
       table->Delete(row);
     }
   }
   else
     std::cout<<"table not found"<<std::endl;   
}

void TwikkiManager::Register(std::string key, ITable &table)
{
   mTable.insert({key,&table});
}

}
