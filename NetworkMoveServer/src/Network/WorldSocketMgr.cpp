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
    sLogMgr->Print("Le serveur a été démarré correctement");
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
        sLogMgr->Message("Nouvelle connection de %s", nSocket->GetRemoteAddress().ToString().c_str());
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
            sLogMgr->Debug("Supression d'un WorldSession");
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
