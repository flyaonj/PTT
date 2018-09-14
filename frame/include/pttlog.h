#ifndef _PTT_LOG
#define _PTT_LOG

#include <string>
#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"


#define PTT_LOG_ENABLE
#ifdef PTT_LOG_ENABLE
#define PTT_LOG_DEBUG_ENABLE
#define PTT_LOG_INFO_ENABLE
#define PTT_LOG_WARN_ENABLE
#define PTT_LOG_ERROR_ENABLE
#define PTT_LOG_FATAL_ENABLE
#endif

using std::string;
using log4cpp::Category;
using log4cpp::PropertyConfigurator;

#define DEFAULT_LOG_CONF_FILE "./conf/log4cpp.conf"

namespace ptt
{
namespace pub
{

//定义各种日志宏
//声明一个日志类成员
#define DECLARE_PTT_LOG() ptt::pub::Log log

//声明一个类的静态日志成员变量
#define DECLARE_PTT_STATIC_LOG() static ptt::pub::Log log

//定义一个类的静态日志成员变量
#define CREATE_PTT_STATIC _LOG(_class, _name)  ptt::pub::Log _class::log; 

#define CREATE_PTT_LOG(_name) \
log.Init(_name);

#ifdef PTT_LOG_DEBUG_ENABLE
#define logDebug(_fmt,...) \
try{ \
    if(log.getLog()->isDebugEnabled()) \
    log.getLog()->debug(_fmt, ##__VA_ARGS__); \
}catch(...) {}
#else
#define logDebug(_fmt,...)
#endif

#ifdef PTT_LOG_INFO_ENABLE
#define logInfo(_fmt,...) \
try{ \
    if(log.getLog()->isInfoEnabled()) \
    log.getLog()->info(_fmt, ##__VA_ARGS__); \
}catch(...){}
#else
#define logInfo(_fmt,...)
#endif


#ifdef PTT_LOG_WARN_ENABLE
#define logWarn(_fmt,...) \
try{ \
    if(log.getLog()->isWarnEnabled()) \
    log.getLog()->warn(_fmt, ##__VA_ARGS__); \
}catch(...){}
#else
#define logWarn(_fmt,...)
#endif

#ifdef PTT_LOG_ERROR_ENABLE
#define logError(_fmt,...) \
try{ \
    if(log.getLog()->isErrorEnabled()) \
    log.getLog()->error(_fmt, ##__VA_ARGS__); \
}catch(...){}
#else
#define logError(_fmt,...)
#endif


#ifdef PTT_LOG_FATAL_ENABLE
#define logFatal(_fmt,...) \
try{ \
    if(log.getLog()->isFatalEnabled()) \
    log.getLog()->fatal(_fmt, ##__VA_ARGS__); \
}catch(...){}
#else
#define logFatal(_fmt,...)
#endif

class Log
{
private:
    static Log _instance;
    Category* _category;
    string _category_Name;
    
public:
    Log();
    Log(const string& name);

    ~Log();
    void Init(const string& name);
    void Format(string& destStr, const char* format, ...);
    string getCalssName(const string& className);
    void SetPriority(const  int& priority);

    Category* getLog()
    {
        return _category;
    }

public:
    //静态方式
    static void Start(const string& configFile);
};
}
}

#endif