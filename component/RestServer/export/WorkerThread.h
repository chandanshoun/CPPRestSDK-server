#ifndef _WORKERTHREAD_H
#define _WORKERTHREAD_H
#include "thread.h"
#include "workqueue.h"

class WorkerThread
{
  private:
    std::thread *tid;
    static WorkerThread* workerInstance;

  public:
    CWorkQueue* wmsgQueue;
    WorkerThread();
    virtual ~WorkerThread();
    virtual void Run();
    virtual void start();
    static WorkerThread* getThreadInstance()
   {
      if(workerInstance==NULL)
         workerInstance=new WorkerThread();
        return workerInstance;
   }
};

#endif
