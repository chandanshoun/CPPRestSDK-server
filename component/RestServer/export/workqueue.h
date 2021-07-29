#ifndef WORKQUEUE_H
#define WORKQUEUE_H
#include "messagequeue.h"
#include "workitem.h"

using namespace Queue;

class CWorkQueue : public MessageQueue<CWorkItem>
{
 public:
  CWorkQueue() {};
  ~CWorkQueue() {};

 private:
  bool OnRun(CWorkItem *item);
};

#endif

