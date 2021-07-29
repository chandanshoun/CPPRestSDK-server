#ifndef __TWIKKIREQUEST__H
#define __TWIKKIREQUEST__H
#include "IRequest.h"

class TwikkiRequest : public IRequest
{
   private:
   std::map<std::string, int> *effortsList;

   public:
   TwikkiRequest(std:: string key, std::string tname): IRequest(key, tname), effortsList(new std::map<std::string, int>){}
   ~TwikkiRequest(){}
   void setEfforts(std::string category, int effort)
   {
     auto itr=effortsList->find(category);
     if(itr!=effortsList->end())
     {
        int e=itr->second;
        e+=effort;
        itr->second=e;
     }
     else
       effortsList->insert({category,effort}); 
   }
   std::map<std::string, int>* getEfforts(){ return effortsList;}
};

#endif
