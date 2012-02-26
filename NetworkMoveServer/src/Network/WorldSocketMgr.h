#ifndef WORLDSOCKETMGR_H
#define WORLDSOCKETMGR_H

#include "Singleton/Singleton.h"
#include "Opcode.h"
#include <SFML/Network.hpp>

class WorldSocketMgr //NE JAMAIS INSTANCIÉ CETTE CLASSE DIRECTEMENT !!! TOUJOURS PASSÉ PAR LE SINGLETON sWorldSocketMgr
{
    friend class Singleton<WorldSocketMgr>;

    public:

    WorldSocketMgr();//Instanciable seulement via un Singleton
    ~WorldSocketMgr();

    void StartNetwork();
    void StopNetwork();

    void Update(uint32 uiDiff);
    void IncommingConnection(sf::TcpSocket *nSocket);

    private:

    sf::TcpListener listener;
    std::vector<WorldSession*> m_sessionMap;
};

#define sWorldSocketMgr Singleton<WorldSocketMgr>::GetInstance()

#endif // WORLDSOCKETMGR_H
