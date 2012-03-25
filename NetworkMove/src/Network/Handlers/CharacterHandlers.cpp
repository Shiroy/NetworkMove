#include "Network/WorldSocket.h"
#include "Network/Opcode.h"

void WorldSocket::SendCharacterEnum()
{
    sf::Packet data;
    data << uint16(CMSG_CHAR_ENUM);

    SendPacket(data);
}
