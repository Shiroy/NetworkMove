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

#ifndef RESSOURCE_MGR_H
#define RESSOURCE_MGR_H

#include <Singleton/Singleton.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum RessourceType
{
    RESSOURCE_TYPE_MAP = 0,
    RESSOURCE_TYPE_SPRITE = 1,
    RESSOURCE_TYPE_SOUND = 2,
    RESSOURCE_TYPE_MUSIC = 3,
};

class RessourceManager
{
    friend class Singleton<RessourceManager>;

    public:
    RessourceManager(); //Ne jamais instancié cette classe directement !! Toujour utilisé le Singleton sRessourceMgr !!
    ~RessourceManager();

    private:

    std::map<uint64, RessourceType> m_ressourceIndex;

    std::map<uint64, sf::SoundBuffer> m_soundBufferIndex; //Son et musiques
    std::map<uint64, sf::Image> m_spriteIndex; //Pour les sprites
};

#define sRessourceMgr Singleton<RessourceManager>::GetInstance()

#endif
