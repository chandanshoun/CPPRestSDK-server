#include "restconnection.h"
#include "workqueue.h"
#include "WorkerThread.h"
#include "workitem.h"
#include "RestRequest.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#pragma comment(lib, "cpprest_2_10")

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#define TRACE(msg)            cout << msg
#define TRACE_ACTION(a, k, v) cout << a << L" (" << k << L", " << v << L")\n"

namespace REST
{
        RESTServer* RESTServer::restInstance=NULL;

        void RESTServer::printJson(
                       json::value const & jvalue,
                       utility::string_t const & prefix)
                       {
                           cout << prefix << jvalue.serialize() << endl;
                       }


        RESTServer::RESTServer()
        {
            msgQueue=new CWorkQueue();
            WorkerThread *WorkerInstance=WorkerThread::getThreadInstance();
            WorkerInstance->wmsgQueue=msgQueue;
            WorkerInstance->start();
        }

void RESTServer::handle_get(http_request request)
{
   TRACE("\nhandle GET\n");

   CWorkItem *item = new RestRequest(request,1);
   msgQueue->AddItem(item);   
}


void RESTServer::handle_post(http_request request)
{
   TRACE("\nhandle POST\n");

   CWorkItem *item = new RestRequest(request,0);
   msgQueue->AddItem(item);   
}

void RESTServer::handle_put(http_request request)
{
   TRACE("\nhandle PUT\n");

   CWorkItem *item = new RestRequest(request,2);
   msgQueue->AddItem(item);   
}

void RESTServer::handle_delete(http_request request)
{
   TRACE("\nhandle DEL\n");

   CWorkItem *item = new RestRequest(request,3);
   msgQueue->AddItem(item);   
}

        void RESTServer::Run()
        {
           http_listener listener("http://127.0.0.1:35248");

           listener.support(methods::GET,  [this](http_request request){ this->handle_get(request);});
           listener.support(methods::POST, [this](http_request request){ this->handle_post(request);});
           listener.support(methods::PUT,  [this](http_request request){ this->handle_put(request);});
           listener.support(methods::DEL,  [this](http_request request){ this->handle_delete(request);});

           try
           {
             listener
              .open()
              .then([&listener]() {TRACE("\nstarting to listen\n"); })
              .wait();

              while (true);
           }
           catch (exception const & e)
          {
            cout << e.what() << endl;
          }
        }

        std::thread* RESTServer::start()
        {
          std::thread* restThread=new std::thread(&RESTServer::Run,this);
          tid=restThread;
          return tid;
        }
}
