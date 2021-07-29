#ifndef __DBUPDATE__H
#define __DBUPDATE__H

#include "thread.h"
#include "twikkimanager.h"
#include "stdafx.h"

class DBUpdateThread : public Thread
{
  private:
    static DBUpdateThread* dbInstance;

  public:
    DBUpdateThread();
    ~DBUpdateThread();
    void Run();
    void start();
    void updateDB();
    void deleteQuery(int, std::string, std::string);
    static DBUpdateThread* getThreadInstance()
   {
      if(dbInstance==NULL)
         dbInstance=new DBUpdateThread();
        return dbInstance;
   }
};

#endif
