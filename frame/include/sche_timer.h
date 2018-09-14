#ifndef _PTT_SCHE_TIMER_H
#define _PTT_SCHE_TIMER_H

#include <list>
#include "Poco/Foundation.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Subsystem.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include "sys_base.h"

using Poco::Runnable;
using Poco::Thread;
using Poco::Util::Application;
using Poco::Util::Subsystem;
using Poco::FastMutex;
using Poco::Mutex;
using Poco::SharedPtr;

namespace ptt{
    namespace sche{

        #define MAX_TIMER (WORD32) 5000
        #define INVALID_TIMER (WORD32) 0

        struct TimerEntry;

        class ScheTimerCtr;
        typedef void (*OnTimerPfn_t)(TimerEntry *);

        typedef void (ScheTimerCtr::*SCHTimerPROC_t)(TimerEntry *);

        enum
	    {
		    LOOP_TIMER = 0, //40s
		    REL_TIMER = 1
	    };

        struct TimerEntryLink
        {
            TimerEntry* head;
            TimerEntry* tail;
        };

        struct TimerWheel
        {
            TimerEntryLink *pItems; //定时器时间槽列表
            int iItemSize;

            unsigned long long ullStart;//当前时间戳
	        long long llStartIdx; //当前时间槽位号
        };

        struct TimerEntry
        {
            WORD32 wIdx; // 定时器ID，唯一标识
            TimerEntry* pPrev;
            TimerEntry* pNext;
            TimerEntryLink* pLink;

            unsigned long long ullExpireTime;
            
            //超时回调函数相关属性
            void *pArg; 
            //OnTimerPfn_t fn;
            SCHTimerPROC_t proc;
        }; 

        struct TimerPool
        {
            std::list<WORD32> freeElements;//可用的定时器资源
            TimerEntry* timers;
        };

        class Timerable
        {
            public:
                virtual void OnTimerCall(BYTE timeno,WORD32 extra) = 0;
        };



        class ScheTimerCtr:public Subsystem,public Runnable
        {
            public:
                ScheTimerCtr();
                void startSystem(Application& app);
                virtual void run();
                virtual const char* name() const;
            public:
                typedef void (*pTimerCallBack)(BYTE timeno,WORD32 extra);

                //glbal or static function
                WORD32 SetTimer(BYTE timeno, WORD32 countms, WORD32 extra, pTimerCallBack fn);                
                WORD32 SetLoopTimer(BYTE timeno, WORD32 countms, WORD32 extra, pTimerCallBack fn);

                WORD32 SetTimer(BYTE timeno, WORD32 countms, WORD32 extra, Timerable& target);
                WORD32 SetLoopTimer(BYTE timeno, WORD32 countms, WORD32 extra, Timerable& target);

                //kill timer
                void KillTimer(WORD32 dwTimerID);
            protected:         
                virtual void initialize(Application& app);
                virtual void uninitialize();
                ~ScheTimerCtr();

            private: 

                WORD32 SetTimerImp(WORD32 countms, char type, SharedPtr<Runnable> pTarget);               
                void AllocateRes(int iTimerWheelSize);
                TimerEntry* GetTimerEntry(); 
                void RecycleTimerEntry(TimerEntry* timer);

                int AddTimeOut(TimerEntry* item, unsigned long long allNow); 
                void RemoveTimeOut(TimerEntry* item);
                void TakeAllTimeout(unsigned long long allNow,TimerEntryLink *apResult);
                void event_loop();
                void OnTimerProcessEvent( TimerEntry *);
            private:
                Thread m_thread; //对应操作系统线程  
                TimerWheel* m_timerWheel; //时间轮  
                TimerPool* m_timerPool;       
                FastMutex m_ResMutex;
                Mutex m_TimeMutex;
        };


    }
}

#endif