#ifndef OPCODE_H
#define OPCODE_H

struct OpcodeHandler
{
    uint16 opcode;
    const char *opcodeName;
    uint8 status;
    void (WorldSocket::*handler)(sf::Packet&);
};

void RegisterOpcode(uint16 opcode, const char* opName, uint8 status, void (WorldSocket::*handler)(sf::Packet&));

#define REGISTER_OPCODE(opcode, status, handler) RegisterOpcode(opcode, #opcode, status, handler)

enum Statut
{
    STATUT_NEVER,
    STATUT_LOGIN_SCREEN,
    STATUT_CHARACTER_SELECTION,
    STATUT_INGAME
};

enum Opcode
{
    MSG_NULL = 0x0000,
    CMSG_AUTH_TRY = 0x0001,
    SMSG_AUTH_TRY = 0x0002,
    MSG_LAST_OPCODE,
};

#endif
