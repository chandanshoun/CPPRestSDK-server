#ifndef __IQUERY__H
#define __IQUERY__H
#include <string>
#include <memory>
#include "tablerow.h"
#include <iostream>

class IQuery
{
   private:

   public:
   std::string tname;
   IQuery():tname("dummy"){}
   virtual ~IQuery(){}
   virtual void BuildQuery(std::shared_ptr<TableRow>)=0;
   virtual void executeQuery()=0;
};

#endif
