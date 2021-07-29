#ifndef __IMODEL__H
#define __IMODEL__H
#include <string>
#include <memory>
#include "tablerow.h"
#include "IQuery.h"
#include "IRequest.h"
#include <iostream>

class IModel
{
   private:
   static IModel *instance;

   public:
   IModel();
   virtual ~IModel();
   static IModel *getInstance(std::string);
   virtual void BuildfromDB()=0; 
   virtual void Insert(std::shared_ptr<IQuery>)=0;
   virtual void Delete(std::shared_ptr<TableRow>)=0;
   virtual void Update(std::shared_ptr<IQuery>)=0;
   virtual void Query(std::shared_ptr<IRequest>)=0;
};

#endif
