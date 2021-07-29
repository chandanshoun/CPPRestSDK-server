#ifndef _THREAD_H
#define _THREAD_H
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

class Thread
{
   public:

   std::chrono::system_clock::time_point timePoint;
   std::thread *threadId;
   virtual void Run()=0;
   virtual void start()=0;
   Thread(){}
   virtual ~Thread(){}
};


#endif
