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
