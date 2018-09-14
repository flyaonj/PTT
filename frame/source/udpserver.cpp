#include "udpserver.h"
#include "co_routine.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/AutoPtr.h"
#include "Poco/Util/AbstractConfiguration.h"

using Poco::AutoPtr;
using Poco::Net::SocketAddress;
using Poco::Util::AbstractConfiguration;
using ptt::udp::RecvThread;
using ptt::udp::Server;


void udpserverHandle(void* arg)
{

}   


RecvThread::RecvThread(const string& acceptor,const SocketAddress& address):
m_acceptor(acceptor),m_socekt(address),m_status(kStopped)
{
}

RecvThread::~RecvThread()
{
    m_thread.join();
}

void RecvThread::run()
{
}

void RecvThread::start()
{
    m_thread.start(*this);
}


Server::Server()
{
    CREATE_PTT_LOG("UDPServer");
}

Server::~Server()
{

}


const char* Server::name() const
{
    return "UDP Server";
}


void Server::initialize(Application& app)
{
    AutoPtr<AbstractConfiguration> pAcceptorsConfig(app.config().createView(PTT_UDP_ACCEPTOR_PRE));

    AbstractConfiguration::Keys acceptors;
    pAcceptorsConfig->keys(acceptors);

	for (AbstractConfiguration::Keys::const_iterator it = acceptors.begin(); it != acceptors.end(); ++it)
    {
	    AutoPtr<AbstractConfiguration> pConfig(pAcceptorsConfig->createView(*it));                

        string ipaddr = pConfig->getString("ipaddr");
        string port = pConfig->getString("ipport");

        logDebug("UDPAcceptors: [%s]:[%s]", ipaddr.c_str(), port.c_str());

        //为每一个控制面地址创建报文收发线程
        try
        {
            RecvThreadPtr recv(new RecvThread(*it, SocketAddress(ipaddr, port)));
            recv_threads.push_back(recv);
        }
        catch(Poco::Exception& exc)
        {
            logFatal("Create UDP Socket Accetor error[%s]", exc.what());
        }
        
    }
}


void Server::uninitialize()
{

}


void Server::startSystem(Application& app)
{  
}       
        





