#include <iostream>
#include <string>

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/Option.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/ThreadPool.h"

#include "pttlog.h"
#include "buffer.h"
#include "udpserver.h"
#include "sche_timer.h"
#include "co_routine.h"



using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Net::DatagramSocket;
using Poco::Net::SocketAddress;
using Poco::ThreadPool;
using Poco::Thread;

using  ptt::sche::Timerable;
using  ptt::sche::ScheTimerCtr;


#if 0
static void *createRedisClient(void* arg)
{
    co_enable_hook_sys();

    REDIS_ENDPOINT endpoints[1] = {
        { "127.0.0.1", 6379 },
        //{ "127.0.0.1", 6380 },
        //{ "127.0.0.1", 6381 },
    };

    REDIS_CONFIG conf = {
        (REDIS_ENDPOINT*)&endpoints,
        1,
        10000,
        5000,
        20,
        1,
    };


    RedisClient*  client = new RedisClient(conf);
}
#endif


int g_timerIndex = 0;
WORD32 g_TimerNo = 0;
Thread g_thread;

struct Functor
{
	void operator () ()
	{
        Application::instance().getSubsystem<ScheTimerCtr>().KillTimer(g_TimerNo);
	}
};


void TimerCallBack(BYTE timeno,WORD32 extra)
{
    poco_warning_f3(Application::instance().logger().get("logger1"),"TimerCallBack: %d,%d,%d", (int)timeno, (int)extra, g_timerIndex); 

    if(timeno == 10)
    {
        g_timerIndex++;
        if(g_timerIndex >=5)
        {
            g_thread.startFunc(Functor());
        } 
    }    
}

class PocServer: public ServerApplication,public Timerable
{
    private:
    DECLARE_PTT_LOG();
    public:
        PocServer()
        {
            CREATE_PTT_LOG("POCSERVER");
            addSubsystem(new ptt::sche::ScheTimerCtr);
            addSubsystem(new ptt::udp::Server);
        }

        ~PocServer()
        {

        }

    public:
        virtual void OnTimerCall(BYTE timeno,WORD32 extra)
        {
            poco_warning_f3(logger().get("logger1"),"TimerCallBack: %d,%d,%d", (int)timeno, (int)extra, g_timerIndex);

            if(timeno == 10)
            {
                g_timerIndex++;
                if(g_timerIndex >=5)
                {
                    g_thread.startFunc(Functor());
                } 
            }    
        }


    protected:
        void initialize(Application& self)
        {
            std::string appdir = config().getString("application.dir");
            loadConfiguration(appdir + "../conf/frame.properties");                        
            ServerApplication::initialize(self);
        }

	    void uninitialize()
	    {
		    ServerApplication::uninitialize();
	    }        

        void defineOptions(OptionSet& options)
        {
            ServerApplication::defineOptions(options);

            options.addOption(
                Option("help","h","display help information on command line arguments")
                .required(false)
                .repeatable(false));
        }


    	void handleOption(const std::string& name, const std::string& value)
        {
    		ServerApplication::handleOption(name, value);
        }
        
        int main(const std::vector<std::string>& args)
        {
            logDebug("POC MAIN");
            //getSubsystem<PTT::UDP::Server>().startSystem(*this);

            getSubsystem<ptt::sche::ScheTimerCtr>().startSystem(*this);

            for(int i=1;i<11;i++)
            {
                //g_TimerNo = getSubsystem<PTT::Sche::ScheTimerCtr>().SetLoopTimer(i,500 ,1024,TimerCallBack);
                g_TimerNo = getSubsystem<ptt::sche::ScheTimerCtr>().SetLoopTimer(i,500 ,1024,*this);
            }
            waitForTerminationRequest();

            return Application::EXIT_OK;
        } 
};


int main(int argc, char** argv)
{
    ptt::pub::Log::Start("../conf/log4cpp.conf");
	PocServer app;
	return app.run(argc, argv);
}


