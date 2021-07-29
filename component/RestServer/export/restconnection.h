#ifndef _RESTCONNECTION_H
#define _RESTCONNECTION_H
#include "workqueue.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;


namespace REST
{
class RESTServer
{
    private:
        std::thread *tid;
        static RESTServer* restInstance;
        CWorkQueue* msgQueue;
        std::map<utility::string_t, utility::string_t> dictionary;

    public:
        static RESTServer* getThreadInstance()
        {
          if(restInstance==NULL)
            restInstance=new RESTServer();
          return restInstance;
        }

        void printJson(
             json::value const & jvalue,
              utility::string_t const & prefix);
        void handle_put(http_request request);
        void handle_post(http_request request);
        void handle_get(http_request request);
        void handle_delete(http_request request);
        RESTServer();
        ~RESTServer(){}
        CWorkQueue* getMessageQueue(){return msgQueue;}
        virtual std::thread* start();
        void Run();
};
}

#endif
