#include "workqueue.h"
#include "workitem.h"
#include "WorkerThread.h"

WorkerThread* WorkerThread::workerInstance=NULL;

void WorkerThread::start()
{
   std::thread* workThread=new std::thread(&WorkerThread::Run,this);
   tid=workThread;
}

WorkerThread::WorkerThread()
{

}

WorkerThread::~WorkerThread()
{
  tid->join();
}


void WorkerThread::Run()
{
   std::cout<<"WorkerThread running now"<<std::endl;
   while(true)
   {
       CWorkItem *msg=wmsgQueue->popItem();
       if(msg)
         msg->Run();
  }
}
