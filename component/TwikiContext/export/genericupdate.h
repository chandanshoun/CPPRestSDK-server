#ifndef __GENERICUPDATE__H
#define __GENERICUPDATE__H
#include "Itable.h"
#include "IModel.h"
#include "tablerow.h"
#include <iostream>
#include <memory>

template <typename TName, typename TQuery> class GenericUpdate : public ITable
{
  public:
  void Insert(std::shared_ptr<TableRow>);
  void Update(std::shared_ptr<TableRow>);
  void Delete(std::shared_ptr<TableRow>);

};

template <typename TName, typename TQuery> inline void GenericUpdate<TName, TQuery>::Update(std::shared_ptr<TableRow> row)
{
  std::cout<<"generic Update called"<<std::endl;
  std::shared_ptr<TQuery> singleQuery(new TQuery());
  singleQuery->BuildQuery(row);
  singleQuery->executeQuery();
  IModel *model=IModel::getInstance(singleQuery->tname);
  model->Update(singleQuery);
}

template <typename TName, typename TQuery> inline void GenericUpdate<TName, TQuery>::Delete(std::shared_ptr<TableRow> row)
{
  std::cout<<"generic Delete called"<<std::endl;
  IModel *model=IModel::getInstance(row->getTableName());
  model->Delete(row);
}

template <typename TName, typename TQuery> inline void GenericUpdate<TName, TQuery>::Insert(std::shared_ptr<TableRow> row)
{
  std::cout<<"generic Insert called"<<std::endl;
  std::shared_ptr<TQuery> singleQuery(new TQuery());
  singleQuery->BuildQuery(row);
  singleQuery->executeQuery();
  IModel *model=IModel::getInstance(singleQuery->tname);
  model->Insert(singleQuery);
}

#endif
