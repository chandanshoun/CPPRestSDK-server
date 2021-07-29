// workitem.h: interface for the WorkItem class.
#ifndef WORKITEM_H
#define WORKITEM_H
#include <iostream>
#include <memory>

class CWorkItem
{
  public :
    CWorkItem() {}
    virtual ~CWorkItem() {}

    virtual void Run() = 0;
};

#endif
