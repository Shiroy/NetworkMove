#ifndef WORLDSOCKET_H
#define WORLDSOCKET_H

#include <SFML/Network.hpp>
#include <Util/SharedDefine.h>
#include <queue>

class App;

class WorldSocket
{
    public:

    WorldSocket(App *appInstance);
    ~WorldSocket();

    sf::IpAddress GetServerAddress() { return m_serverAddress; }
    void SetServerAddress(sf::IpAddress val) { m_serverAddress = val; }

    bool ConnectTo(sf::IpAddress host = sf::IpAddress(), uint16 port = 3241);
    void Update(uint32 uiDiff);
    void Close();

    void SendPacket(sf::Packet &pkt);

    private:

    void NetworkThread(); //Gère la reception de données par la socket (l'envoir est géré dans WorldSocket::Update)

    sf::TcpSocket m_socket;
    sf::IpAddress m_serverAddress;

    sf::Thread *m_thread;
    sf::Mutex m_sendMutex;
    sf::Mutex m_receiveMutex;

    std::queue<sf::Packet> m_queuedPacket; //Pour la reception
    std::queue<sf::Packet> m_sendQueuePacket; //Pour l'envoie

    App *m_appInstance;
};

#endif // WORLDSOCKET_H
