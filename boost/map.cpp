#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;


class Task
{

   public:

   string name, task;
   Task(string nm, string tm):name(nm),task(tm){

      cout<<"Cestructor called"<<endl;

}
   ~Task()
   {
      cout<<"Destructor called"<<endl;
   }
};

int main()
{
  map<string, multimap<string, shared_ptr<Task>>> mapList;
  shared_ptr<Task> sp(new Task("agcf-8","completed")); 
  mapList["chandanJan"].insert({"agcf",sp});
  mapList["chandanJan"].insert({"agcf",make_shared<Task>(Task("agcf-6","completed"))});
  mapList["chandanJan"].insert({"agcf",make_shared<Task>(Task("agcf-7","completed"))});

  for(auto mainItr=mapList.begin();mainItr!=mapList.end();mainItr++)
  {
     cout<<" key is "<<mainItr->first<<endl;
     auto innerItr=mainItr->second;
     for(auto itr=innerItr.begin();itr!=innerItr.end();itr++)
       cout<<itr->first<<" "<<itr->second->name<<" "<<itr->second->task<<endl;
  }

  auto one = mapList["chandanJan"].lower_bound("agcf"); 
  auto last = mapList["chandanJan"].upper_bound("agcf"); 
      
  while (one != last)     
  { 
     if(one->second->name=="agcf-3")
      {
         one->second->name="chandu";
      }
     one++;
  }     

  for(auto mainItr=mapList.begin();mainItr!=mapList.end();mainItr++)
  {
     cout<<" key is "<<mainItr->first<<endl;
     auto innerItr=mainItr->second;
     for(auto itr=innerItr.begin();itr!=innerItr.end();itr++)
       cout<<itr->first<<" "<<itr->second->name<<" "<<itr->second->task<<endl;
  }

  cout<<"here search and delete part"<<endl;

  auto itr=mapList["chandanJan"].find("agcf");

  while(itr!=last)
  {
     if(itr->second->name=="chandu")
     {
       mapList["chandanJan"].erase(itr);
     }
     itr++;
  }

  auto itr6=mapList["chandanJan"].find("agcf");
  for(auto mainItr : mapList)
  {
     cout<<" key is "<<mainItr.first<<endl;
     auto innerItr=mainItr.second;
     for(auto itr : innerItr)
       cout<<itr.first<<" "<<itr.second->name<<" "<<itr.second->task<<endl;
  }

  return 0;
} 
