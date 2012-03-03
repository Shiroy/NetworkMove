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

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SFML/System.hpp>
#include "Singleton/Singleton.h"
#include "Network/WorldSession.h"
#include "Network/WorldSocketMgr.h"

class World //NE JAMAIS INSTANCIÉ CETTE CLASSE DIRECTEMENT !!! TOUJOURS PASSÉ PAR LE SINGLETON sWorld
{
    friend class Singleton<World>;

    public:

    World();
    ~World();

    void InitWorld();
    void Run();
    void DestroyWorld();

    private:

    bool m_run;
    sf::Clock m_clock;
};

#define sWorld Singleton<World>::GetInstance()
#endif
