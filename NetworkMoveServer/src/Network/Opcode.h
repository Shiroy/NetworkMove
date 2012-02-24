#ifndef OPCODE_H
#define OPCODE_H

#include <map>
#include <string>
#include <Util/SharedDefine.h>
#include <Network/WorldSession.h>

namespace sf //Name space de la SFML
{
    class Packet;
};

/*!
 *\enum Statut
 *\brief Liste les différents status possibles pour un opcode
 */
enum Statut
{
    STATUS_NEVER,/*!< L'opcode est interdit, tout packet contenant cette opcode sera détruit*/
    STATUS_AUTHENTIFICATION,/*!< La recpetion de cette opcode est autorisé uniquement lors de la connexion d'un joueur (opcode d'authentification)*/
    STATUS_CHARACTER_SELECTION,/*!< La reception de cette opcode est autorisé uniquement lors de selection d'un personnage (creation, suppression et selection de personnage)*/
    STATUS_INGAME /*!< La recption de cette opcode est autorisé lorsque le joueur est en jeu (le reste des opcode)*/
};

/*!
 *\struct OpcodeHandler
 *\brief Structure décrivant un opcode
 *
 *Cette structure enregistre toutes les informations concernant un opcode.
 */
struct OpcodeHandler
{
    uint16 opcode; /*!< Id de l'opcode*/
    const char *opcodeName; /*!< Nom de l'opcode*/
    Statut status; /*!< Status dans lequelle l'opcode est autorisé*/
    void (WorldSession::*handler)(sf::Packet&); /*!< Pointeur vers le handler de l'opcode*/
};

/*!
 *\def REGISTER_OPCODE(opcode, status, handler)
 *
 *\brief Enregistre un nouvel opcode et lui associe un status et un handler
 *
 *Cette macro enregistre un nouvel opcode en lui associant un status et un handler. \warning Utiliser cette macro plutôt que directement la fonction RegisterOpcode !
 */
#define REGISTER_OPCODE(opcode, status, handler) RegisterOpcode(opcode, #opcode, status, handler)

/*!
 *\enum Opcode
 *
 *\brief Enumère les différends opcodes
 *
 *Cette macro énumère les différents opcodes utilisés par le jeu.
 *\par Convention de nommage:
 *- Un opcode commençant par CMSG est un opcode utilisé uniquement dans le sens client => serveur.
 *- Un opcode commençant par SMSG est un opcode utilisé uniquement dans le sens serveur => client.
 *- Un opcode commençant par MSG est un opcode pouvant être utilisé dans les deux sens.
 */
enum Opcode
{
    MSG_NULL = 0x0000, /*!< L'opcode nul, jamais utilisé*/
    CMSG_AUTH_TRY = 0x0001, /*!< Opcode envoyé par le client pour demander une authetification:
    *\par Structure:
    *- \c std::string \c version ; actuellement 0.0.1a
    *- \c std::string \c pseudo ; pseudo du joueur
    *- \c std::string \c password ; mot de passe du joueur
    */
    SMSG_AUTH_TRY = 0x0002, /*!< Opcode de réponse à CMSG_AUTH_TRY
    *\par Structure
    *- \c uint8 \c erreur ; Code d'erreur (0 si aucune erreur)
    */
    MSG_LAST_OPCODE,
};

extern OpcodeHandler opcodeMap[MSG_LAST_OPCODE];

void InitOpcodeTable();

const char *LookupOpcodeName(uint16 opcode);

/*!
 *\deprecated void RegisterOpcode(uint16 opcode, const char* opName, Statut status, void (WorldSocket::*handler)(sf::Packet&))
 *
 *\brief En registre un nouvel opcode
 *
 *Enregistre un nouvel opcode en lui associant un handler
 *
 *\param opcode Id de l'opcode
 *\param opName Nom de l'opcode
 *\param status Indique à quelle moment du jeu l'opcode est autorisé
 *\param *handler Pointeur vers le handler de l'opcode. C'est toujours une fonction du type: \code void WorldSocket::handler (sf::Packet&) \endcode
 */
void RegisterOpcode(Opcode opcode, const char* opName, Statut status, void (WorldSession::*handler)(sf::Packet&));

#endif
