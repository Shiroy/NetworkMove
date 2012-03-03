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

/*!
*\file main.cpp
*\brief Fichier contenant la fonction main
*/

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
