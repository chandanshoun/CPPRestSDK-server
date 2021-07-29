#ifndef _QUERYOPERATION_H
#define _QUERYOPERATION_H
#include "operation.h"
#include "RestRequest.h"
#include "ctable.h"
#include "dbhandler.h"
#include "jsonParser.h"
#include <cpprest/json.h>
#include "jsonresponse.h"

//using namespace web;
//using namespace web::http;


class QueryOperation : public Operation
{
  private:
  http_request mrequest;

  public:
  QueryOperation();
  QueryOperation(http_request &);
  virtual ~QueryOperation();
  void execute();
};

#endif
