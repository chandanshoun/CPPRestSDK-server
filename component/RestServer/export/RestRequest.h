#ifndef _RESTREQUEST_H
#define _RESTREQUEST_H

#include "workitem.h"
#include<iostream>
#include<memory>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

enum {POST = 0, GET = 1, PUT = 2, DELETE = 3};

class RestRequest : public CWorkItem
{
  private:
    std::string msg;
    http_request mrequest;
    int type;

  public :
    RestRequest();
    RestRequest(http_request&, int);
    virtual ~RestRequest() {};
    void Run();
};

#endif

