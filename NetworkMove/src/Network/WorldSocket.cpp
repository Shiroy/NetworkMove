#include <Network/WorldSocket.h>

WorldSocket::WorldSocket()
{
    m_socket.SetBlocking(false);
}

WorldSocket::~WorldSocket()
{
    //dtor
}

void WorldSocket::Update(uint32 uiDiff)
{
    sf::Packet data;

    if(!m_queuedPacket.empty())
    {
        data = m_queuedPacket.front();
        if(m_socket.Send(data) == sf::Socket::Done)
        {
            m_queuedPacket.pop();
        }
    }

    if(m_socket.Receive(data) != sf::Socket::Done);
        return;
}

bool WorldSocket::ConnectTo(sf::IpAddress host, uint16 port)
{
    if(host != sf::IpAddress::None)
        SetServerAddress(host);

    return m_socket.Connect(m_serverAddress, port);
}

void WorldSocket::SendPacket(sf::Packet &data)
{
    m_queuedPacket.push(data);
}

void WorldSocket::Close()
{
    m_socket.Disconnect();
}

