#include <Network/Opcode.h>

OpcodeHandler opcodeMap[MSG_LAST_OPCODE];

void RegisterOpcode(int16 opcodeNumber, uint8 status, const char* n_opcodeName, void (WorldSession::*hdl)(sf::Packet&))
{
    OpcodeHandler newOpcode;

    newOpcode.opcode = opcodeNumber;
    newOpcode.opcodeName = n_opcodeName;
    newOpcode.handler = hdl;
    newOpcode.status = status;

    opcodeMap[opcodeNumber] = newOpcode;
}

void InitOpcodeTable()
{
    REGISTER_OPCODE(MSG_NULL, STATUS_AUTHENTIFICATION, &WorldSession::NullHandler);
    REGISTER_OPCODE(CMSG_AUTH_TRY, STATUS_AUTHENTIFICATION, &WorldSession::HandleAuthTry);
    REGISTER_OPCODE(SMSG_AUTH_TRY, STATUS_NEVER, &WorldSession::NullHandler);
}

const char *LookupOpcodeName(uint16 opcode)
{
    if(opcode >= MSG_LAST_OPCODE)
        return NULL;
    else
        return opcodeMap[opcode].opcodeName;
}
