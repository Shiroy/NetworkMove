#ifndef OPCODE_H
#define OPCODE_H

#include <map>
#include <string>
#include <Util/SharedDefine.h>
#include <Network/WorldSession.h>

namespace sf
{
    class Packet;
};

enum Status
{
    STATUS_AUTHENTIFICATION,
    STATUS_CHARACTER_SELECTION,
    STATUS_INGAME,
};

struct OpcodeHandler
{
    uint16 opcode;
    const char *opcodeName;
    void (WorldSession::*handler)(sf::Packet& data);
    uint8 status;
};

enum Opcode
{
    MSG_NULL = 0x00,
    CMSG_AUTH_TRY = 0x01,
    MSG_LAST_OPCODE,
};

extern OpcodeHandler opcodeMap[MSG_LAST_OPCODE];

void RegisterOpcode(int16 opcodeNumber, uint8 status, const char* n_opcodeName, void (WorldSession::*)(sf::Packet&));
void InitOpcodeTable();

const char *LookupOpcodeName(uint16 opcode);

#define REGISTER_OPCODE(opcode, status, handler) RegisterOpcode(opcode, status, #opcode, handler)

#endif
