#include <iostream>

#include "pttlog.h"

using ptt::pub::Log;


//单例
Log Log::_instance;


void Log::Start(const string& configFile)
{
    try
    {
        if(!configFile.empty())
        {
            log4cpp::PropertyConfigurator::configure(configFile);
        }
    }
    catch(log4cpp::ConfigureFailure &f)
    {
        std::cout << "start Log error" <<f.what() << std::endl;
    }
}


Log::Log():_category(NULL),_category_Name("")
{
}


Log::Log(const string& name):_category(NULL)
{
    if(!name.empty())
    {
        Init(name);
    }
    _category_Name = name;
}

Log::~Log()
{

}


void Log::Init(const string& name)
{        
    _category = &log4cpp::Category::getInstance(name);
}

void Log::SetPriority(const  int& priority)
{
    if(_category!=NULL)
    {
        _category->setPriority(priority);
    }
}











