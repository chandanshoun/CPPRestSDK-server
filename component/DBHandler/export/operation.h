#ifndef _OPERATION_H
#define _OPERATION_H
#include "jsonpacket.h"
class Operation
{
  public:
  Operation();
  virtual ~Operation();
  virtual void execute();
};

#endif
