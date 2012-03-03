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

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <Singleton/Singleton.h>
/*!
 *\file Log.h
 *\author Eryldor
 *\brief Définis une classe permetant de gérer les logs de façon efficace
 */


/*!
 *\class Log
 *\author Eryldor
 *\brief Classe gérant les logs.
 *\details Cette classe gère les log du client et du serveur. Pour le moment, elle gère uniquement la console. A l'avenir d'autre classe dérivée seront ajouté afin d'écrire des logs dans des fichier par exemple.
 */
class Log
{
    friend class Singleton<Log>;

    public:

    Log();
    ~Log();

    /*!
     *\brief Log un message d'erreur
     *\author Eryldor
     *\details Affiche un message d'erreur dans la console. Le message affiché sera automatiquement précédé de "[ERREUR] ".
     *\param msg Message à afficher
     */
    void Error(const char *msg, ...);

    /*!
     *\brief Affiche un message de log
     *\author Eryldor
     *\details Affiche un message de log. Le message sera automatiquement précédé par "[LOG] ".
     *\param msg Message à afficher
     */
    void Message(const char *msg, ...);

    /*!
    *\brief Affiche un message dans la console
    *\author Eyldor
    *\details Affiche un message dans la cnsole sans aucune modification du message (contrairment à Log::Error et Log::Message)
    *\param msg Message à afficher
    */
    void Print(const char *msg, ...);

    /*!
     *\brief Affiche un message de debug
     *\author Eryldor
     *\details Affiche un message de debug dans la console. Le message sera automatiquement précédé par "[DEBUG] ".
     *\param msg Message à afficher
     */
     void Debug(const char *msg, ...);
};

#define sLogMgr Singleton<Log>::GetInstance()

#endif
