#include<iostream>
#include<thread>
#include "thread.h"
#include "restconnection.h"
#include "dbupdate.h"

using namespace std;
using namespace REST;

int main()
{
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

  RESTServer* restServerThread=RESTServer::getThreadInstance();
  std::thread* restThread=restServerThread->start();

  DBUpdateThread *dbInstance=DBUpdateThread::getThreadInstance();
  dbInstance->start();

  //waiting restThread to join
  restThread->join();
  return 0;
}
