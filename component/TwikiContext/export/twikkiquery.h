#ifndef __TWIKKIQUERY__H
#define __TWIKKIQUERY__H
#include "stdafx.h"
#include<memory>
#include<string>
#include "tablerow.h"
#include "IQuery.h"

class TwikkiQuery : public IQuery
{
  private:
  std::shared_ptr<sql::PreparedStatement> prep_stmt;
  std::string mQuery;

  public:
  std::string tname, name, month, category, task;
  int efforts, id;
  TwikkiQuery():mQuery("SELECT * from employee where id=?"){}
  ~TwikkiQuery(){}
  void BuildQuery(std::shared_ptr<TableRow>);
  void executeQuery();
};


#endif
