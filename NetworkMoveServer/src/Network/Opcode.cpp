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

#include <Network/Opcode.h>

OpcodeHandler opcodeMap[MSG_LAST_OPCODE];

void RegisterOpcode(Opcode opcodeNumber, const char* n_opcodeName, Statut status, void (WorldSession::*hdl)(sf::Packet&))
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
    REGISTER_OPCODE(CMSG_CHAR_ENUM, STATUS_CHARACTER_SELECTION, &WorldSession::HandleCharEnum);
}

const char *LookupOpcodeName(uint16 opcode)
{
    if(opcode >= MSG_LAST_OPCODE)
        return NULL;
    else
        return opcodeMap[opcode].opcodeName;
}
