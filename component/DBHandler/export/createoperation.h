#ifndef _CREATEOPERATION_H
#define _CREATEOPERATION_H
#include "operation.h"
#include "RestRequest.h"
#include "ctable.h"
#include "dbhandler.h"
#include "jsonParser.h"
#include <cpprest/json.h>
#include "jsonresponse.h"

using namespace web;
using namespace web::http;


class CreateOperation : public Operation
{
  private:
  http_request mrequest;

  public:
  CreateOperation();
  CreateOperation(http_request &);
  virtual ~CreateOperation();
  void execute();
};

#endif
