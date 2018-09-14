#include "sche_timer.h"
#include <sys/time.h>

using namespace ptt::sche;


static unsigned long long GetTickMS()
{
#if defined( __LIBCO_RDTSCP__) 
	static uint32_t khz = getCpuKhz();
	return counter() / khz;
#else
	struct timeval now = { 0 };
	gettimeofday( &now,NULL );
	unsigned long long u = now.tv_sec;
	u *= 1000;
	u += now.tv_usec / 1000;
	return u;
#endif
}

template <class T,class TLink>
void RemoveFromLink(T *ap)
{
	TLink *lst = ap->pLink;
	if(!lst) return ;

	if( ap == lst->head )
	{
		lst->head = ap->pNext;
		if(lst->head)
		{
			lst->head->pPrev = NULL;
		}
	}
	else
	{
		if(ap->pPrev)
		{
			ap->pPrev->pNext = ap->pNext;
		}
	}

	if( ap == lst->tail )
	{
		lst->tail = ap->pPrev;
		if(lst->tail)
		{
			lst->tail->pNext = NULL;
		}
	}
	else
	{
		ap->pNext->pPrev = ap->pPrev;
	}

	ap->pPrev = ap->pNext = NULL;
	ap->pLink = NULL;
}

template <class TNode,class TLink>
void inline AddTail(TLink*apLink,TNode *ap)
{
	if( ap->pLink )
	{
		return ;
	}
	if(apLink->tail)
	{
		apLink->tail->pNext = (TNode*)ap;
		ap->pNext = NULL;
		ap->pPrev = apLink->tail;
		apLink->tail = ap;
	}
	else
	{
		apLink->head = apLink->tail = ap;
		ap->pNext = ap->pPrev = NULL;
	}
	ap->pLink = apLink;
}


template <class TNode,class TLink>
void inline Join( TLink*apLink,TLink *apOther )
{
	//printf("apOther %p\n",apOther);
	if( !apOther->head )
	{
		return ;
	}
	TNode *lp = apOther->head;
	while( lp )
	{
		lp->pLink = apLink;
		lp = lp->pNext;
	}
	lp = apOther->head;
	if(apLink->tail)
	{
		apLink->tail->pNext = (TNode*)lp;
		lp->pPrev = apLink->tail;
		apLink->tail = apOther->tail;
	}
	else
	{
		apLink->head = apOther->head;
		apLink->tail = apOther->tail;
	}

	apOther->head = apOther->tail = NULL;
}

template <class TNode,class TLink>
void inline PopHead( TLink*apLink )
{
	if( !apLink->head ) 
	{
		return ;
	}
	TNode *lp = apLink->head;
	if( apLink->head == apLink->tail )
	{
		apLink->head = apLink->tail = NULL;
	}
	else
	{
		apLink->head = apLink->head->pNext;
	}

	lp->pPrev = lp->pNext = NULL;
	lp->pLink = NULL;

	if( apLink->head )
	{
		apLink->head->pPrev = NULL;
	}
}



ScheTimerCtr::ScheTimerCtr()
{

}

void ScheTimerCtr::startSystem(Application& app)
{
    m_thread.start(*this);
}

void ScheTimerCtr::initialize(Application& app)
{
    AllocateRes(60*1000);
}


void ScheTimerCtr::run()
{
    event_loop();
}


void ScheTimerCtr::uninitialize()
{

}

const char* ScheTimerCtr::name() const
{
    return "TimerService";
}


ScheTimerCtr::~ScheTimerCtr()
{
} 


void ScheTimerCtr::AllocateRes(int iTimerWheelSize)
{

    //初始化时间轮容器
    m_timerWheel = (TimerWheel*)calloc(1,sizeof(TimerWheel));
    m_timerWheel->iItemSize = iTimerWheelSize;
    m_timerWheel->ullStart = GetTickMS();
    m_timerWheel->llStartIdx = 0;
    m_timerWheel->pItems = (TimerEntryLink*)calloc(m_timerWheel->iItemSize, sizeof(TimerEntryLink));

    //初始化定时器资源池
    m_timerPool = new TimerPool;

    for(WORD32 i=0;i< MAX_TIMER;i++)
    {
        m_timerPool->freeElements.push_back(i+1);
    }

    m_timerPool->timers = (TimerEntry*)calloc(MAX_TIMER,sizeof(TimerEntry));
}


TimerEntry* ScheTimerCtr::GetTimerEntry()
{
    FastMutex::ScopedLock lock(m_ResMutex);

    if(m_timerPool->freeElements.empty())
    {
        return NULL;
    }    

    WORD32 idx = m_timerPool->freeElements.front();
    m_timerPool->freeElements.pop_front();
    TimerEntry* item =  &(m_timerPool->timers[idx-1]);
    item->wIdx = idx;
    return item;
}


void ScheTimerCtr::RecycleTimerEntry(TimerEntry* timer)
{
    if(timer->pArg)
    {
        free(timer->pArg);
    }
    
    memset(timer,0,sizeof(TimerEntry));    
    FastMutex::ScopedLock lock(m_ResMutex);
    m_timerPool->freeElements.push_back(timer->wIdx);
}

int  ScheTimerCtr::AddTimeOut(TimerEntry* item, unsigned long long allNow)
{
    if(m_timerWheel->ullStart == 0)
    {
        m_timerWheel->ullStart = allNow;
        m_timerWheel->llStartIdx = 0;
    }

    if(allNow < m_timerWheel->ullStart)
    {
        return -1;
    }

    if(item->ullExpireTime < allNow)
    {
        return -1;
    }

	unsigned long long diff = item->ullExpireTime - m_timerWheel->ullStart;

    if( diff >= (unsigned long long)m_timerWheel->iItemSize )
    {
		diff = m_timerWheel->iItemSize - 1;        
    }

    AddTail( m_timerWheel->pItems + ( m_timerWheel->llStartIdx + diff ) % m_timerWheel->iItemSize , item );

    return 0;
}


void ScheTimerCtr::RemoveTimeOut(TimerEntry* item)
{
    RemoveFromLink<TimerEntry,TimerEntryLink>(item);
}


void ScheTimerCtr::TakeAllTimeout(unsigned long long allNow,TimerEntryLink *apResult)
{
    if(m_timerWheel->ullStart == 0)
    {
        m_timerWheel->ullStart = allNow;
        m_timerWheel->llStartIdx = 0;
    }

    if(allNow < m_timerWheel->ullStart)
    {
        return ;
    }

	int cnt = allNow - m_timerWheel->ullStart + 1;

    if( cnt > m_timerWheel->iItemSize )
	{
		cnt = m_timerWheel->iItemSize;
	}

    if( cnt < 0 )
	{
		return;
	}

    for( int i = 0;i<cnt;i++)
	{
		int idx = ( m_timerWheel->llStartIdx + i) % m_timerWheel->iItemSize;
		Join<TimerEntry,TimerEntryLink>( apResult,m_timerWheel->pItems + idx  );
	}

    m_timerWheel->ullStart = allNow;
    m_timerWheel->llStartIdx += cnt - 1 ; 
}


void ScheTimerCtr::event_loop()
{
    TimerEntryLink* timeout = (TimerEntryLink*)calloc(1, sizeof(TimerEntryLink));
    for(;;)
    {
        Thread::current()->sleep(1);

        Mutex::ScopedLock lock(m_TimeMutex);

        memset( timeout,0,sizeof(TimerEntryLink) );    

        unsigned long long now = GetTickMS();
		TakeAllTimeout(now,timeout );   

        TimerEntry *lp = timeout->head;

        while(lp)
        {
            PopHead<TimerEntry,TimerEntryLink>(timeout);
            if(lp->ullExpireTime < now)
            {
                int ret = AddTimeOut(lp, now);
                if (!ret) 
				{
					lp = timeout->head;
					continue;
				}                
            }

            if(lp->proc)
            {
                //lp->fn(lp);
                (this->*(lp->proc))(lp);
            }

            lp = timeout->head;
        } 
    }
}



void ScheTimerCtr::KillTimer(WORD32 dwTimerID)
{
    if(dwTimerID < 1 || dwTimerID > MAX_TIMER)
    {
        return;
    }

    Mutex::ScopedLock lock(m_TimeMutex);
    TimerEntry* item = &(m_timerPool->timers[dwTimerID-1]);
    RemoveTimeOut(item);
    RecycleTimerEntry(item);
}

class CallableHolder:public Runnable
{
    public:
        CallableHolder(ScheTimerCtr::pTimerCallBack callable, BYTE timeno, WORD32 extra):
        _callback(callable),
        _timeno(timeno),
        _extra(extra)
        {
        }

        ~CallableHolder()
        {

        }

        void run()
        {
            _callback(_timeno, _extra);
        }

    private:
        ScheTimerCtr::pTimerCallBack _callback;
        BYTE _timeno;
        WORD32 _extra;
};

struct stTimeArg_t
{
    char type;
	WORD32 countms;
	// char timeno;
    // unsigned long extra;
    // ScheTimerCtr::pTimerCallBack fn;
    SharedPtr<Runnable> _pRunnableTarget;        
};

WORD32 ScheTimerCtr::SetTimer(BYTE timeno, WORD32 countms, WORD32 extra, pTimerCallBack fn)
{
    return SetTimerImp(countms, REL_TIMER,  new CallableHolder(fn, timeno,extra));
}


WORD32 ScheTimerCtr::SetLoopTimer(BYTE timeno, WORD32 countms, WORD32 extra, pTimerCallBack fn)
{
    return SetTimerImp(countms, LOOP_TIMER, new CallableHolder(fn, timeno,extra));
}

WORD32 ScheTimerCtr::SetTimerImp(WORD32 countms, char type, SharedPtr<Runnable> pTarget)
{
    if(countms <= 0)
    {
        return INVALID_TIMER;
    }

    Mutex::ScopedLock lock(m_TimeMutex);
    TimerEntry* item = GetTimerEntry();
    if(item == NULL)
    {
        return INVALID_TIMER;
    }
    stTimeArg_t* pArg = new stTimeArg_t;
    //pArg->timeno = timeno;
	pArg->countms = countms;
	pArg->type = type;
	//pArg->fn = fn;
	//pArg->extra = extra;
    pArg->_pRunnableTarget = pTarget;

    item->pArg = pArg;
	item->proc = &ScheTimerCtr::OnTimerProcessEvent;
	
	unsigned long long now = GetTickMS();
	item->ullExpireTime = now + countms;
	int ret = AddTimeOut(item, now);

	if(ret!=0)
	{
        RecycleTimerEntry(item);
		return ret;
	}	

    return item->wIdx;
}

void ScheTimerCtr::OnTimerProcessEvent( TimerEntry * item)
{
    //首先将定时器从队列中删除
    Mutex::ScopedLock lock(m_TimeMutex);

    RemoveTimeOut(item);
	if(item->pArg)
	{
		stTimeArg_t* pArg  = (stTimeArg_t*)item->pArg;

		//调用定时器回调函数
		//pArg->fn(pArg->timeno, pArg->extra);
        pArg->_pRunnableTarget->run();

		//循环定时器
		if(pArg->type == LOOP_TIMER)
		{
			//将定时器控制块重新加入定时器队列
			unsigned long long now = GetTickMS();
			item->ullExpireTime = now + pArg->countms;//重新计算时间

			int ret = AddTimeOut(item, now);
			if(ret!=0)
			{
                RecycleTimerEntry(item);
			}
		}
		else
		//非循环定时器
		{
			//执行完毕之后释放定时器相关控制块
            RecycleTimerEntry(item);
		}
	}
}

class TimerableHolder:public Runnable
{
    public:
        TimerableHolder(Timerable& callable, BYTE timeno, WORD32 extra):
        _callable(callable),
        _timeno(timeno),
        _extra(extra)
        {
        }

        ~TimerableHolder()
        {

        }

        void run()
        {
            _callable.OnTimerCall(_timeno, _extra);
        }

    private:
		Timerable& _callable;
        BYTE _timeno;
        WORD32 _extra;
};


WORD32 ScheTimerCtr::SetTimer(BYTE timeno, WORD32 countms, WORD32 extra, Timerable& target)
{
	return SetTimerImp(countms, REL_TIMER, new TimerableHolder(target, timeno,extra));
}

WORD32 ScheTimerCtr::SetLoopTimer(BYTE timeno, WORD32 countms, WORD32 extra, Timerable& target)
{
	return SetTimerImp(countms, LOOP_TIMER, new TimerableHolder(target, timeno, extra));
}
















