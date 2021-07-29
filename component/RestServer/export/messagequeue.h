#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#include<iostream>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<queue>
#include<string>
#include <map>
#include <condition_variable>
using namespace std;

namespace Queue
{

template <typename T> class MessageQueue
{
   private:
   std::queue <T *> msgQueue;

   public:
   MessageQueue(){}  
   std::mutex lock;
   void AddItem(T *msg);
   std::condition_variable m_condVar;
   T* popItem();
};

template <typename T> inline void MessageQueue<T>::AddItem(T *msg)
{
     cout<<"Add Item called";
     std::unique_lock<std::mutex> mlock(lock);
     msgQueue.push(msg);
     m_condVar.notify_one();
}

template <typename T> inline T* MessageQueue<T>::popItem()
{
     cout<<"Pop Item called";
     T *msg=NULL;
     std::unique_lock<std::mutex> mlock(lock);
     m_condVar.wait(mlock, [&](){return !msgQueue.empty();});
     if(!msgQueue.empty())
     {
       msg=msgQueue.front();
       msgQueue.pop();
       return msg;
     }
     return msg;
}

}

#endif
