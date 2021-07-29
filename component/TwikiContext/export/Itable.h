#ifndef __TTABLE__H
#define __TTABLE__H
#include <string>
#include <memory>
#include "tablerow.h"
#include <iostream>

class ITable
{
   private:

   public:

   ITable(){}
   virtual ~ITable(){}
   virtual void Insert(std::shared_ptr<TableRow>)=0;
   virtual void Delete(std::shared_ptr<TableRow>)=0;
   virtual void Update(std::shared_ptr<TableRow>)=0;
};



#endif
