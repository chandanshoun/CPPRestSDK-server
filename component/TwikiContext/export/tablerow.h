#ifndef __TABLEROW__H
#define __TABLEROW__H
#include<string>

class TableRow
{
  private:

  int mid;
  std::string mtname, maction, mname, mmonth;

  public:
  TableRow():mid(0), mtname("dummy"), maction("dummy"), mname("dummy"), mmonth("dummy")
  {
  }

  ~TableRow(){}

  void setID(int id){mid=id;}
  void setTableName(std::string tname){mtname=tname;}
  void setAction(std::string action){maction=action;}
  void setName(std::string name){mname=name;}
  void setMonth(std::string month){mmonth=month;}

  int getID(){return mid;}
  std::string getTableName(){return mtname;}
  std::string getAction(){return maction;}
  std::string getName(){return mname;}
  std::string getMonth(){return mmonth;}
};

#endif
