#include <Network/WorldSocket.h>
#include <cassert>
#include <iostream>

WorldSocket::WorldSocket(App *appInstance) : m_appInstance(appInstance)
{
    m_thread = NULL;
}

WorldSocket::~WorldSocket()
{
    if(m_thread)
    {
        m_thread->Terminate();
        delete m_thread;
        m_thread = NULL;
    }
}

void WorldSocket::Update(uint32 uiDiff)
{
    sf::Packet data;

    m_sendMutex.Lock();
    if(!m_sendQueuePacket.empty())
    {
        data = m_sendQueuePacket.front();
        m_sendQueuePacket.pop();
    }
    m_sendMutex.Unlock();

    if(data.GetDataSize() != 0)
    {
        m_socket.Send(data);
    }

    //Traiter les packet entrant
}

bool WorldSocket::ConnectTo(sf::IpAddress host, uint16 port)
{
    if(m_thread)
    {
        m_thread->Terminate();
        delete m_thread;
        m_thread = NULL;
    }

    m_thread = new sf::Thread(&WorldSocket::NetworkThread, this);
    assert(m_thread);
    m_thread->Launch();

    if(host != sf::IpAddress::None)
        SetServerAddress(host);

    return (m_socket.Connect(m_serverAddress, port) == sf::Socket::Done) ? true : false;
}

void WorldSocket::SendPacket(sf::Packet &data)
{
    m_sendMutex.Lock();
    m_sendQueuePacket.push(data);
    m_sendMutex.Unlock();
}

void WorldSocket::NetworkThread()
{
    sf::Packet data;

    //std::cout << "Thread reseau" << std::endl;

    if(m_socket.Receive(data) == sf::Socket::Disconnected)
    {
        //Gerer la deconnexion (ex : Crash serveur)
        while(m_sendQueuePacket.size() != 0) //On purge la liste d'attente d'envoie
            m_sendQueuePacket.pop();

        while(m_queuedPacket.size() != 0) //On purge la file de reception
            m_queuedPacket.pop();
    }
    else
    {
        m_receiveMutex.Lock();
        m_queuedPacket.push(data);
        m_receiveMutex.Unlock();
        std::cout << "Reponse du serveur !" << std::endl;
    }
}

void WorldSocket::Close()
{
    m_socket.Disconnect();
    if(m_thread)
    {
        m_thread->Terminate();
        delete m_thread;
        m_thread = NULL;
    }
}

