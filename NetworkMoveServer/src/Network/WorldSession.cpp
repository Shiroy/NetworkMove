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
    m_queuedPacket.push(pkt);
}

void WorldSession::HandleAuthTry(sf::Packet &data)
{
    std::string version, pseudo, password;
    data >> version;
    data >> pseudo;
    data >> password;

    std::cout << "Pseudo : " << pseudo << std::endl;
    std::cout << "Password : " << password << std::endl;
}

void WorldSession::NetworkThread()
{
    while(1)
    {
        sf::Packet data;
        if(m_socket->Receive(data) == sf::Socket::Disconnected)
        {
            std::cout << "Deconnexion de " << m_socket->GetRemoteAddress() << std::endl;
            m_toDestroy = true;
            return;
        }
        else
        {
            std::cout << "Reception de donné" << std::endl;
            m_recvMutex.Lock();
            m_queuedPacket.push(data);
            m_recvMutex.Unlock();
        }

    }
}
