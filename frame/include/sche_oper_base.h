#ifndef _PTT_SCHE_OPER_BASE_H_
#define _PTT_SCHE_OPER_BASE_H_

#include "Poco/Foundation.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/SharedPtr.h"
#include "Poco/PriorityNotificationQueue.h"
#include "sys_base.h"
#include "buffer.h"

using  Poco::Runnable;
using  Poco::Thread;
using  Poco::PriorityNotificationQueue;
using  Poco::SharedPtr;
using  Poco::Notification;


namespace ptt{
namespace sche{

typedef SharedPtr<ptt::Buffer> ScheMsgPtr;
class ScheMsgNofication:public Notification    
{
    public:
        ScheMsgNofication(ScheMsgPtr data):
        _data(data)
        {

        }

        ScheMsgPtr data() const
        {
            return _data;
        }
        
    private:
        ScheMsgPtr _data;
};


class ScheOperBase: public Runnable
{
    public:
        ScheOperBase();
        virtual ~ScheOperBase();
        void init();
        RESULT ScheFsmCreate(const char* lpname, WORD32 dwStackSize, Thread::Priority prio);
    public:
        virtual void run();
        void  ScheTaskEntry();   
    protected:

    private:
        Thread m_ScheThread;
        PriorityNotificationQueue m_Msgque;
};
    }
}

#endif