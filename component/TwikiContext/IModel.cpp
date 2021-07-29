#include "IModel.h"
#include "twikki.h"

IModel* IModel::instance=NULL;

IModel::IModel()
{

}

IModel::~IModel()
{


}

IModel * IModel::getInstance(std::string tname)
{
    if(tname=="employee")
      instance=Twikki::getInstance();
    return instance;
}

