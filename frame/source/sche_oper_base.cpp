#include "sche_oper_base.h"
#include "Poco/AutoPtr.h"

using ptt::sche::ScheOperBase;

ScheOperBase::ScheOperBase()
{
    init();
}


ScheOperBase::~ScheOperBase()
{
}


void ScheOperBase::init()
{
    
}

RESULT ScheOperBase::ScheFsmCreate(const char* lpname, WORD32 dwStackSize, Thread::Priority prio)
{
    if(NULL==lpname)
    {
        return FAILURE;
    }

    m_ScheThread.setName(lpname);
    m_ScheThread.setPriority(prio);
    m_ScheThread.setStackSize(dwStackSize);
    m_ScheThread.start(*this);
    return SUCCESS;
}


void ScheOperBase::run()
{
    ScheTaskEntry();
}


void ScheOperBase::ScheTaskEntry()
{
    
}
