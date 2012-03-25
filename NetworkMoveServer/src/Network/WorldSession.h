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

#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <SFML/Network.hpp>
#include <Util/SharedDefine.h>
#include <SFML/System.hpp>
#include <queue>
#include "Log/Log.h"

class WorldSession
{
    public:

    WorldSession(sf::TcpSocket *socket);
    virtual ~WorldSession();

    void Update(const uint32 uiDiff);

    uint8 GetStatus();
    void SetStatus(uint8 nStatus);

    bool ToDestroy()
    {
        return m_toDestroy;
    }

    void SendPacket(sf::Packet &pkt);

    //Handlers

    void NullHandler(sf::Packet &recv){}
    void HandleAuthTry(sf::Packet &data);

    //Selection des personnages

    void HandleCharEnum(sf::Packet &recv);

    protected:

    private:

    void NetworkThread();

    sf::TcpSocket *m_socket;
    std::queue<sf::Packet> m_queuedPacket;
    std::queue<sf::Packet> m_sendQueuePacket;

    sf::Thread *m_thread;
    sf::Mutex m_recvMutex;
    sf::Mutex m_sendMutex;

    uint8 m_status;
    bool m_toDestroy;
};

#endif // WORLDSESSION_H
