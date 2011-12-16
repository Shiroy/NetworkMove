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

    void SetStatut(uint8 nStatut)
    {
        m_statut = nStatut;
    }

    uint8 GetStatut()
    {
        return m_statut;
    }

    //Handler

    void NullHandler(sf::Packet &) {}
    void HandleAuthResponse(sf::Packet &);

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

    uint8 m_statut;
};

#endif // WORLDSOCKET_H
