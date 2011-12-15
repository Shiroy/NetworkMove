#include <Network/WorldSocketMgr.h>
#include <iostream>

WorldSocketMgr::WorldSocketMgr()
{
    InitOpcodeTable();
}

WorldSocketMgr::~WorldSocketMgr()
{
    for(int i = 0 ; i < m_sessionMap.size() ; i++)
    {
        if(m_sessionMap[i])
            delete m_sessionMap[i];
    }
}

void WorldSocketMgr::StartNetwork()
{
    if(listener.Listen(3241) != sf::Socket::Done)
        exit(1);
    listener.SetBlocking(false);
}

void WorldSocketMgr::StopNetwork()
{
    listener.Close();
}

void WorldSocketMgr::Update(uint32 uiDiff)
{
    sf::TcpSocket *nSocket = new sf::TcpSocket;
    if(listener.Accept(*nSocket) == sf::Socket::Done) //Gestion des nouvelle connection
    {
        std::cout << "Nouvelle connection de " << nSocket->GetRemoteAddress() << std::endl;
        IncommingConnection(nSocket);
    }
    else
        delete nSocket;

    for(std::vector<WorldSession*>::iterator i = m_sessionMap.begin() ; i < m_sessionMap.end() ; i++)
    {
        WorldSession *session = (*i);
        if(!session)
            continue;
        if(session->ToDestroy())
        {
            std::cout << "Supression d'un WorldSession" << std::endl;
            m_sessionMap.erase(i);
        }

        session->Update(uiDiff);
    }
}

void WorldSocketMgr::IncommingConnection(sf::TcpSocket *nSocket)
{
    WorldSession *nSession = new WorldSession(nSocket);

    m_sessionMap.push_back(nSession);
}
