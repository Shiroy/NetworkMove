#include <iostream>
#include <Unit/Unit.h>
#include <Network/WorldSocket.h>
#include <App/App.h>

int main()
{
    App theApp;

    theApp.Init();
    theApp.Run();
    theApp.Exit();

    return 0;
}
