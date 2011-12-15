#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <Util/Singleton.h>
#include <Network/WorldSession.h>
#include <Network/WorldSocketMgr.h>

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
