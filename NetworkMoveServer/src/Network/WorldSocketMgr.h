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
