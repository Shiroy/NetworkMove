#include <Network/WorldSession.h>
#include <Network/Opcode.h>
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
    delete m_socket;
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
        std::cout << "Reception de l'opcode " << op.opcode << " (" << op.opcodeName << ")" << std::endl;

        if(op.status == m_status)
        {
            (this->*op.handler)(data);
        }
        else
        {
            std::cout << "Reception d'un opcode invalide à cette phase de jeu. Kick !" << std::endl;
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
        std::cout << "Envoie de donné" << std::endl;
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

    std::cout << "Pseudo : " << pseudo << std::endl;
    std::cout << "Password : " << password << std::endl;

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
            std::cout << "Deconnexion de " << m_socket->GetRemoteAddress() << std::endl;
            m_toDestroy = true;
            return;
        }
        else
        {
            //Reception de donnés
            std::cout << "Reception de donné" << std::endl;
            m_recvMutex.Lock();
            m_queuedPacket.push(data);
            m_recvMutex.Unlock();
        }
    }
}
