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

#ifndef WORLDSOCKET_H
#define WORLDSOCKET_H

/*!
 *\file WorldSockect.h
 *\brief Ce fichier contient la déclaration de la classe gérant la socket de connexion avec le serveur
 *\author Eryldor
*/

#include <SFML/Network.hpp>
#include <Util/SharedDefine.h>
#include <queue>

class App;

/*!
 *\class WorldSocket
 *\author Eryldor
 *\brief Cette classe gère la socket de connexion avec le serveur ainsi que les handler des différents opcodes recues
 *
 *\details
 *Cette classe permet de manipuler la socket et donc la connexion avec le serveur. Elle se charge de la connexion, de l'envoie de packets, de la réception des nouvelles données. On y déclare également les différents handlers qui gèreront les packet recus en fonction des opcodes.
 *\par Ajouter un nouvel opcode
 *Pour mettre en place un nouvelle opcode, il y a trois étapes:
 *- Définir l'opcode dans src/Network/Opcode.h. Un opcode se compose d'un identifiant et d'un id unique
 *- Créer le handler dans WorldSocket. La convention de nommage utilisé est la suivant : Handler{Description du handler} ; ex : Pour un opcode qui fait envoie des infos sur une guilde on utilisera HandleGuildInfo. Un handler est toujour du types \e void et a toujour en paramètre une référence sur un \e sf::Packet.
 *- Associer l'opcode et son handler. Cette association ce fait par la macros REGISTER_OPCODE qui prend comme paramètre le define de l'opcode, son status et un pointeur vers son handler. Il y a trois statut possible : opcode interdit, autorisé sur l'écran de connexion, autorisé lors du choix d'un personnage, autorisé quand en jeu.
*/
class WorldSocket
{
    public:

    /*!
    *\brief Constructeur
    *
    *Constructeur de la classe WorldSocket. Cette fonction a besoin d'un pointeur sur une instance valide de la classe App afin de pouvoir lui transmettre les différentes information envoyées par le serveur.
    *
    *\param *appInstance Pointeur vers une istance valide de la classe App
    */
    WorldSocket(App *appInstance);

    /*!
    *\brief Destructeur
    *
    *Détruit l'instance de la classe. Attention cela ne libère pas la mémoire occupé par l'instance de App passé au constructeur
    */
    ~WorldSocket();

    /*!
     *\brief Retourne l'adresse IP du serveur
     *
     *Retourne l'adresse IP du serveur auquel le client est connecté
     *
     **\return sf::IpAddress Adresse IP du serveur distant
     */
    sf::IpAddress GetServerAddress() { return m_serverAddress; }
    /*!
     *\brief Modifie l'adresse IP à laquelle le client doit se connecter.
     *
     *Modifie l'adresse IP du serveur auquel le client doit se connecter. Cela ne modifie pas une eventuelle connexion existante.
     *
     *\param m_serverAddress Nouvelle adresse IP.
     */
    void SetServerAddress(sf::IpAddress val) { m_serverAddress = val; }
    /*!
     *\brief Se connecter à un serveur
     *
     *Se connecte au serveur dont l'adresse IP a été envoyé en paramètre. Si le aucune adresse n'est spécifier, la dernière adresse fixé par SetServerAddress est prise.
     *
     *\param host Adresse IP à laquelle se connecter
     *\param port Port de connexion. Par défaut 3241.
     *\return Revoie \c true si la connexion à réussie sinon elle revoie \c false
     */
    bool ConnectTo(sf::IpAddress host = sf::IpAddress(), uint16 port = 3241);
    /*!
     *\brief Mets à jour la socket
     *
     *Cette fonction mets à jour la socket en envoyant les paquets en attente et en recevant les nouveaux arrivés. Lors de la reception d'un nouveau paquet, le handler correspondant à l'opcode reçu est automatiquement appelé. \warning À chaque passage dans cette fonction uniquement un seule paquet est reçue et un seule est envoyé.
     *\param uiDiff Intervalle de temps écoulé depuis le dernier appel à cette fonction en milliseconde.
     */
    void Update(uint32 uiDiff);
    /*!
     *\brief Ferme la connexion ouverte
     *
     *Ferme la connexion ouverte, purge les listes d'attentes d'envoies et de receptions et stop le thread associer à la socket.
     */
    void Close();
    /*!
     *\brief Ajoute un paquet en liste d'attente d'envoie
     *
     *Place un paquet en liste d'attente d'envoie. \attention L'envoie du paquet au serveur n'est pas immédiat mais se fera lors d'un appel à WorldSocket::Update
     */
    void SendPacket(sf::Packet &pkt);
     /*!
      *\brief Définis le nouveau status de la socket.
      */
    void SetStatut(uint8 nStatut)
    {
        m_statut = nStatut;
    }

    uint8 GetStatut()
    {
        return m_statut;
    }

    //Handler

    void NullHandler(sf::Packet &) {}
    void HandleAuthResponse(sf::Packet &);

    private:

    void NetworkThread(); //Gère la reception de données par la socket (l'envoir est géré dans WorldSocket::Update)

    sf::TcpSocket m_socket;
    sf::IpAddress m_serverAddress;

    sf::Thread *m_thread;
    sf::Mutex m_sendMutex;
    sf::Mutex m_receiveMutex;

    std::queue<sf::Packet> m_queuedPacket; //Pour la reception
    std::queue<sf::Packet> m_sendQueuePacket; //Pour l'envoie

    App *m_appInstance;

    uint8 m_statut;
};

#endif // WORLDSOCKET_H
