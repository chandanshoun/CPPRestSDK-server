#ifndef __CTABLE_H
#define __CTABLE_H
#include "jsonpacket.h"
#include "jsonresponse.h"

//CTable Interface
class CTable
{
   private:

   public:
   CTable();
   virtual ~CTable();   
   virtual JsonResponse* getJsonResponse();
   virtual bool ParseTableData(JsonPacket*);
   virtual bool ParseTableDataGet(JsonPacket*);
   virtual bool ParseTableDataDelete(JsonPacket*);
   virtual bool ParseTableDataUpdate(JsonPacket*);
   virtual bool Insert()=0;
   virtual bool Delete()=0;
   virtual bool Update()=0;
   virtual bool Query()=0;
};

#endif

