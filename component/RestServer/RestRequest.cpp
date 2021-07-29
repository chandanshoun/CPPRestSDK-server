#include "RestRequest.h"
#include "createoperation.h"
#include "queryoperation.h"
#include "deleteoperation.h"
#include "updateoperation.h"
#include <iostream>

using namespace std;

RestRequest::RestRequest(http_request &request, int etype):mrequest(request), type(etype)
{

}

RestRequest::RestRequest()
{
}

void RestRequest::Run()
{
  Operation *opr=NULL;
  switch(type)
  {
   case POST:
   {
      std::cout<<"RestRequest workitem called for post"<<std::endl;
      opr=new CreateOperation(mrequest);
      opr->execute();
   }
   break;

   case GET:
   {
      std::cout<<"RestRequest workitem called for get"<<std::endl;
      opr=new QueryOperation(mrequest);
      opr->execute();
   }
   break;

   case DELETE:
   {
      std::cout<<"RestRequest workitem called for delete"<<std::endl;
      opr=new DeleteOperation(mrequest);
      opr->execute();
   }
   break;

   case PUT:
   {
      std::cout<<"RestRequest workitem called for update"<<std::endl;
      opr=new UpdateOperation(mrequest);
      opr->execute();
   }

   break;
   default:
     break;

  }
  if(opr)
   delete opr;
}
