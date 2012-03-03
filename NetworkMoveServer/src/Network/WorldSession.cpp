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

#include "Network/WorldSession.h"
#include "Network/Opcode.h"
#include <cstring>
#include <iostream>
#include <cassert>

WorldSession::WorldSession(sf::TcpSocket *socket)
{
    m_socket = socket;
    m_status = STATUS_AUTHENTIFICATION;
    m_toDestroy = false;
    m_thread = new sf::Thread(&WorldSession::NetworkThread, this);
    assert(m_thread);
    m_thread->Launch();
}

WorldSession::~WorldSession()
{
    if(m_socket)
    {
        m_socket->Disconnect();
        delete m_socket;
    }

    if(m_thread)
    {
        m_thread->Terminate();
        delete m_thread;
        m_thread = NULL;
    }
}

void WorldSession::Update(const uint32 uiDiff)
{
    sf::Packet data;

    m_recvMutex.Lock();
    if(!m_queuedPacket.empty())
    {
        data = m_queuedPacket.front();
        m_queuedPacket.pop();
    }
    m_recvMutex.Unlock();

    if(data.GetDataSize() != 0)
    {
        uint16 opcode;
        data >> opcode;
        OpcodeHandler op = opcodeMap[opcode];
        sLogMgr->Debug("Reception de l'opcode 0x%X (%s)", op.opcode, op.opcodeName);

        if(op.status == m_status)
        {
            (this->*op.handler)(data);
        }
        else
        {
            sLogMgr->Message("Reception d'un opcode invalide à cette phase de jeu : 0x%X (%s). Kick !", op.opcode, op.opcodeName);
            m_socket->Disconnect();
        }
    }

    m_sendMutex.Lock();
    if(!m_sendQueuePacket.empty())
    {
        data = m_sendQueuePacket.front();
        m_sendQueuePacket.pop();
    }
    m_sendMutex.Unlock();

    if(data.GetDataSize() != 0)
    {
        sLogMgr->Debug("Envoie de donné");
        m_socket->Send(data);
    }
}

void WorldSession::SetStatus(uint8 nStatus)
{
    m_status = nStatus;
}

uint8 WorldSession::GetStatus()
{
    return m_status;
}

void WorldSession::SendPacket(sf::Packet &pkt)
{
    m_sendMutex.Lock();
    m_sendQueuePacket.push(pkt);
    m_sendMutex.Unlock();
}

void WorldSession::HandleAuthTry(sf::Packet &data)
{
    std::string version, pseudo, password;
    data >> version;
    data >> pseudo;
    data >> password;

    sLogMgr->Debug("Pseudo : %s", pseudo.c_str());
    sLogMgr->Debug("Password : %s", password.c_str());

    sf::Packet resp;
    resp << uint16(SMSG_AUTH_TRY);
    resp << uint8(0); //Code d'erreur
    SendPacket(resp);
}

void WorldSession::NetworkThread()
{
    while(1)
    {
        sf::Packet data;
        if(m_socket->Receive(data) == sf::Socket::Disconnected)
        {
            //Deconnexion d'un client
            sLogMgr->Message("Deconnexion de %s", m_socket->GetRemoteAddress().ToString().c_str());
            m_toDestroy = true;
            return;
        }
        else
        {
            //Reception de donnés
            sLogMgr->Debug("Reception de donné");
            m_recvMutex.Lock();
            m_queuedPacket.push(data);
            m_recvMutex.Unlock();
        }
    }
}
