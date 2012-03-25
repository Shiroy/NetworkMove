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

#include <World/World.h>

World::World()
{

}

void World::InitWorld()
{
    m_run = true;
    m_clock.restart();
    sWorldSocketMgr->StartNetwork();
}

void World::Run()
{
    while(m_run)
    {
        uint32 uiDiff = m_clock.getElapsedTime().asMilliseconds();
        if(uiDiff < 32) //Au moin 32 miliseconde d'inactivité pour economiser les mprocesseur (changé la valeur si besoin est)
        {
            usleep(32-uiDiff);
        }
        m_clock.restart();

        sWorldSocketMgr->Update(uiDiff);
    }
}

void World::DestroyWorld()
{

}
