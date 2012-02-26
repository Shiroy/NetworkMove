#include <World/World.h>

World::World()
{

}

void World::InitWorld()
{
    m_run = true;
    m_clock.Restart();
    sWorldSocketMgr->StartNetwork();
}

void World::Run()
{
    while(m_run)
    {
        uint32 uiDiff = m_clock.GetElapsedTime().AsMilliseconds();
        if(uiDiff < 32) //Au moin 32 miliseconde d'inactivité pour economiser les mprocesseur (changé la valeur si besoin est)
        {
            usleep(32-uiDiff);
        }
        m_clock.Restart();

        sWorldSocketMgr->Update(uiDiff);
    }
}

void World::DestroyWorld()
{

}
