#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <SFML/Network.hpp>
#include <Util/SharedDefine.h>
#include <SFML/System.hpp>
#include <queue>

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

    protected:

    private:

    void NetworkThread();

    sf::TcpSocket *m_socket;
    std::queue<sf::Packet> m_queuedPacket;

    sf::Thread *m_thread;
    sf::Mutex m_recvMutex;
    sf::Mutex m_sendMutex;

    uint8 m_status;
    bool m_toDestroy;
};

#endif // WORLDSESSION_H
