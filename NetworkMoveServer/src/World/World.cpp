#include <World/World.h>

World::World()
{

}

void World::InitWorld()
{
    m_run = true;
    m_clock.Reset();
    sWorldSocketMgr->StartNetwork();
}

void World::Run()
{
    while(m_run)
    {
        uint32 uiDiff = (uint32)m_clock.GetElapsedTime();
        if(uiDiff < 32) //Au moin 32 miliseconde d'inactivité pour economiser les mprocesseur (changé la valeur si besoin est)
        {
            usleep(32-uiDiff);
        }
        m_clock.Reset();

        sWorldSocketMgr->Update(uiDiff);
    }
}

void World::DestroyWorld()
{

}
