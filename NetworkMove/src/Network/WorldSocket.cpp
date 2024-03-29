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

#include "Network/WorldSocket.h"
#include "App/App.h"
#include "Network/Opcode.h"
#include <cassert>
#include "Log/Log.h"

OpcodeHandler opcodeMap[MSG_LAST_OPCODE];

void RegisterOpcode(uint16 opcode, const char* opName, Statut status, void (WorldSocket::*handler)(sf::Packet&))
{
    OpcodeHandler newOp;
    newOp.opcode = opcode;
    newOp.opcodeName = opName;
    newOp.status = status;
    newOp.handler = handler;

    opcodeMap[opcode] = newOp;
}

WorldSocket::WorldSocket(App *appInstance) : m_appInstance(appInstance)
{
    m_thread = NULL;

    SetStatut(STATUT_LOGIN_SCREEN);

    REGISTER_OPCODE(CMSG_AUTH_TRY, STATUT_NEVER, &WorldSocket::NullHandler);
    REGISTER_OPCODE(SMSG_AUTH_TRY, STATUT_LOGIN_SCREEN, &WorldSocket::HandleAuthResponse);
    REGISTER_OPCODE(CMSG_CHAR_ENUM, STATUT_NEVER, &WorldSocket::NullHandler);
}

WorldSocket::~WorldSocket()
{
    if(m_thread)
    {
        m_thread->terminate();
        delete m_thread;
        m_thread = NULL;
    }
}

void WorldSocket::Update(uint32 uiDiff)
{
    sf::Packet data;

    if(!m_sendQueuePacket.empty())
    {
        m_sendMutex.lock();
        data = m_sendQueuePacket.front();

        if(data.getDataSize() != 0)
        {
            m_socket.send(data);
        }

        m_sendQueuePacket.pop();
        m_sendMutex.unlock();
    }

    //Traite les packet entrant

    data.clear();

    if(m_queuedPacket.size() != 0)
    {
        m_receiveMutex.lock();
        data = m_queuedPacket.front();

        if(data.getDataSize() != 0)
        {
            uint16 opcode;
            data >> opcode;

            OpcodeHandler opHandler = opcodeMap[opcode];

            if(opHandler.status != m_statut)
            {
                sLogMgr->Message("Réception d'un opcode invalide");
                return;
            }

            (this->*opHandler.handler)(data);
        }

        m_queuedPacket.pop();
        m_receiveMutex.unlock();
    }    


}

bool WorldSocket::ConnectTo(sf::IpAddress host, uint16 port)
{
    if(m_thread)
    {
        m_thread->terminate();
        delete m_thread;
        m_thread = NULL;
    }

    m_thread = new sf::Thread(&WorldSocket::NetworkThread, this);
    assert(m_thread);
    m_thread->launch();

    if(host != sf::IpAddress::None)
        SetServerAddress(host);

    return (m_socket.connect(m_serverAddress, port) == sf::Socket::Done) ? true : false;
}

void WorldSocket::SendPacket(sf::Packet &data)
{
    m_sendMutex.lock();
    m_sendQueuePacket.push(data);
    m_sendMutex.unlock();
}

void WorldSocket::NetworkThread()
{
    sf::Packet data;

    //std::cout << "Thread reseau" << std::endl;

    if(m_socket.receive(data) == sf::Socket::Disconnected)
    {
        //Gerer la deconnexion (ex : Crash serveur)
        while(m_sendQueuePacket.size() != 0) //On purge la liste d'attente d'envoie
            m_sendQueuePacket.pop();

        while(m_queuedPacket.size() != 0) //On purge la file de reception
            m_queuedPacket.pop();
    }
    else
    {
        m_receiveMutex.lock();
        m_queuedPacket.push(data);
        m_receiveMutex.unlock();
        sLogMgr->Message("Reponse du serveur !");
    }
}

void WorldSocket::Close()
{
    m_socket.disconnect();
    if(m_thread)
    {
        m_thread->terminate();
        delete m_thread;
        m_thread = NULL;
    }

    while(m_sendQueuePacket.size() != 0) //On purge la liste d'attente d'envoie
        m_sendQueuePacket.pop();

    while(m_queuedPacket.size() != 0) //On purge la file de reception
        m_queuedPacket.pop();
}

void WorldSocket::HandleAuthResponse(sf::Packet &data)
{
    uint8 resp;
    data >> resp;

    sLogMgr->Debug("Code d'authetification %u", resp);

    assert(m_appInstance);
    m_appInstance->AuthResponseReceived(resp);
}

