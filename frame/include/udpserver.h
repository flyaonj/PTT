#ifndef _PTT_UDP_SERVER_H
#define _PTT_UDP_SERVER_H

#include "Poco/Util/Application.h"
#include "Poco/Util/Subsystem.h"
#include "Poco/SharedPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/DatagramSocket.h"
#include "RedisClient.h"


using Poco::Util::Subsystem;
using Poco::Util::Application;
using Poco::SharedPtr;
using Poco::SharedPtr;
using Poco::Runnable;
using Poco::Thread;
using Poco::Net::SocketAddress;
using Poco::Net::DatagramSocket;

namespace ptt{
    namespace udp{


    enum Status {
        kRunning = 1,
        kPaused = 2,
        kStopping = 3,
        kStopped = 4,
    };

    
    
    class RecvThread:public Runnable
    {
        public:
            RecvThread(const SocketAddress& address);
        
            ~RecvThread();

            virtual void run();     

            void start();        
        private:
            DatagramSocket m_socekt;
            Poco::Thread m_thread;    
            Status m_status;                
    };    

        class Server:public Subsystem
        {
            public:
                Server();
                virtual const char* name() const;
                void startSystem(Application& app);
                RedisClient* client;
            protected:         
                virtual void initialize(Application& app);
                virtual void uninitialize();
                ~Server();

            private:       
                typedef  SharedPtr<RecvThread>  RecvThreadPtr;     
                std::vector<RecvThreadPtr>  recv_threads;
                size_t recv_buf_size_;   
                Poco::Thread m_thread; 
        };
    }
}




#endif