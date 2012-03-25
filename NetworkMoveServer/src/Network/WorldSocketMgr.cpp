/*
NetworkMove : un projet de MMORPG éducatif
Copyright (C) 2012  Antoine Wacheux (Eryldor) and the NetworkMove development team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    if(listener.listen(3241) != sf::Socket::Done)
        exit(1);
    listener.setBlocking(false);
    sLogMgr->Print("Le serveur a été démarré correctement");
}

void WorldSocketMgr::StopNetwork()
{
    listener.close();
}

void WorldSocketMgr::Update(uint32 uiDiff)
{
    sf::TcpSocket *nSocket = new sf::TcpSocket;
    if(listener.accept(*nSocket) == sf::Socket::Done) //Gestion des nouvelle connection
    {
        sLogMgr->Message("Nouvelle connection de %s", nSocket->getRemoteAddress().toString().c_str());
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
