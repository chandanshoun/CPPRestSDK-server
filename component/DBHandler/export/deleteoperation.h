#ifndef _DELETEOPERATION_H
#define _DELETEOPERATION_H
#include "operation.h"
#include "RestRequest.h"
#include "ctable.h"
#include "dbhandler.h"
#include "jsonParser.h"
#include <cpprest/json.h>
#include "jsonresponse.h"

using namespace web;
using namespace web::http;

class DeleteOperation : public Operation
{
  private:
  http_request mrequest;

  public:
  DeleteOperation();
  DeleteOperation(http_request &);
  virtual ~DeleteOperation();
  void execute();
};

#endif
