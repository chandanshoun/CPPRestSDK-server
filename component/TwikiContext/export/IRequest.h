#ifndef __IREQUEST__H
#define __IREQUEST__H
#include<string>

class IRequest
{
   private:


   public:
   std::string mtname;
   std::string mkey;
   IRequest(std::string key, std::string tname):mtname(tname), mkey(key){}
   virtual ~IRequest(){}


};
#endif
