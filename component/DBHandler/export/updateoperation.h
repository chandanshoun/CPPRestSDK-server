#ifndef _UPDATEEOPERATION_H
#define _UPDATEOPERATION_H
#include "operation.h"
#include "RestRequest.h"
#include "ctable.h"
#include "dbhandler.h"
#include "jsonParser.h"
#include <cpprest/json.h>
#include "jsonresponse.h"

using namespace web;
using namespace web::http;


class UpdateOperation : public Operation
{
  private:
  http_request mrequest;

  public:
  UpdateOperation();
  UpdateOperation(http_request &);
  virtual ~UpdateOperation();
  void execute();
};

#endif
