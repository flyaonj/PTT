#include "udpserver.h"
#include "co_routine.h"
#include "Poco/Net/DatagramSocket.h"

using namespace Poco::Util;
using namespace Poco::Net;
using namespace ptt::udp;


static REDIS_ENDPOINT endpoints[1] = {
        { "127.0.0.1", 6379 },
        //{ "127.0.0.1", 6380 },
        //{ "127.0.0.1", 6381 },
};

static REDIS_CONFIG conf = {
        (REDIS_ENDPOINT*)&endpoints,
        1,
        10000,
        5000,
        20,
        1,
    };


struct task_t
{
	int id;
    stCoRoutine_t* co;
    stCoCond_t* cond; 
    Server* server;
};


void *routine_task(void *arg)
{
    poco_warning(Application::instance().logger(),"routine_task enter task");  
    
    co_enable_hook_sys();

    poco_warning(Application::instance().logger(),"routine_task end co_enable_hook_sys");  
    

    int id =  ((task_t*)arg)->id;    

    stCoCond_t* cond = ((task_t*)arg)->cond;

    Server* server = ((task_t*)arg)->server;


    if(server->client==NULL && cond!=NULL)
    co_cond_timedwait(cond, -1);

    poco_warning_f1(Application::instance().logger(),"routine_task[id=%d] start task",id);  

    
    for(int i=0;i<2;i++)
    {

        poco_warning_f1(Application::instance().logger(),"routine_task[id=%d] start request",id);  
      
        RedisReplyPtr reply = server->client->redisCommand("SET ID %d", 20);  

        poco_warning_f1(Application::instance().logger(),"routine_task[id=%d] get reply",id);  

        if (reply.notNull()) {
            poco_warning_f1(Application::instance().logger(),"reply= %d" ,reply->type);    
        }
    }

    return 0;
}


void *createRedisClient(void* arg)
{
    co_enable_hook_sys();

    stCoCond_t* cond = ((task_t*)arg)->cond;

    Server* server = ((task_t*)arg)->server;

    poco_warning_f1(Application::instance().logger(),"createRedisClient,Server[%s]",std::string(server->name())); 
    

    if(server->client==NULL)
        server->client = new RedisClient(conf);
        
    co_cond_broadcast(cond);  


    RecvThread* rev  = new RecvThread(SocketAddress("127.0.0.1",10000));

    rev->start();

    return 0;
}


void udpserverHandle(void* arg)
{

    Server* server = (Server*) arg;
    
    stCoEpoll_t * ev = co_get_epoll_ct(); //ct = current thread

    stCoCond_t* cond = co_cond_alloc();
    task_t* task =  new task_t;
    task->cond = cond;
    task->server = server;

    //创建多个协程
    for(int i=0;i<2;i++)
    {
		stCoRoutine_t *co = 0;
        task->id = i+1; 
        co_create( &(task->co),NULL,routine_task,task);                
        co_resume( task->co );   
    }

    stCoRoutine_t *create_co = NULL;
    co_create( &(task->co),NULL,createRedisClient,task);     
    co_resume(task->co);  

	co_eventloop( ev,0,0 );

}   


RecvThread::RecvThread(const SocketAddress& address):m_socekt(address),m_status(kStopped)
{

}

RecvThread::~RecvThread()
{
    m_thread.join();
}

void RecvThread::run()
{
    m_status = kRunning;

    task_t* task =  new task_t;
    task->server = &(Application::instance().getSubsystem<Server>());

    //创建多个协程
    for(int i=0;i<2;i++)
    {
		stCoRoutine_t *co = 0;
        task->id = 10+i+1; 
        co_create( &(task->co),NULL,routine_task,task);     
        co_resume( task->co );   
    }

   	co_eventloop( co_get_epoll_ct(),0,0 );

}

void RecvThread::start()
{
    m_thread.start(*this);
}


Server::Server()
{

}

Server::~Server()
{

}


const char* Server::name() const
{
    return "UDPServer";
}


void Server::initialize(Application& app)
{

}


void Server::uninitialize()
{

}


void Server::startSystem(Application& app)
{
    poco_warning(Application::instance().logger(),"Server::startSystem");
    m_thread.start(&udpserverHandle,this);    
}       
        





