#ifndef RESSOURCE_MGR_H
#define RESSOURCE_MGR_H

#include <Util/Singleton.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum RessourceType
{
    RESSOURCE_TYPE_MAP = 0,
    RESSOURCE_TYPE_SPRITE,
    RESSOURCE_TYPE_SOUND,
    RESSOURCE_TYPE_MUSIC,
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
