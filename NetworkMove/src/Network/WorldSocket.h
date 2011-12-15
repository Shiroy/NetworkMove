#ifndef WORLDSOCKET_H
#define WORLDSOCKET_H

#include <SFML/Network.hpp>
#include <Util/SharedDefine.h>
#include <queue>

class WorldSocket
{
    public:
        WorldSocket();
        ~WorldSocket();

        sf::IpAddress GetServerAddress() { return m_serverAddress; }
        void SetServerAddress(sf::IpAddress val) { m_serverAddress = val; }

        bool ConnectTo(sf::IpAddress host = sf::IpAddress(), uint16 port = 3241);
        void Update(uint32 uiDiff);
        void Close();

        void SendPacket(sf::Packet &pkt);
    protected:
    private:
        sf::TcpSocket m_socket;
        sf::IpAddress m_serverAddress;

        std::queue<sf::Packet> m_queuedPacket;
};

#endif // WORLDSOCKET_H
