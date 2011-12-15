#include <Network/WorldSession.h>
#include <World/World.h>

int main()
{
    /********************
    Ajouter ici l'initialisation du serveur (options, etc)
    ********************/

    sWorld->InitWorld();
    sWorld->Run();
    sWorld->DestroyWorld();

    return 0;
}
