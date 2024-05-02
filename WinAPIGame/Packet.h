#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

enum Type
{
    Connect = 10,
    Disconnect = 20,
    MAX
};

#pragma pack(push, 1)

struct Header
{
    unsigned short length;
    unsigned short type;
};

struct Location
{
    float x;
    float y;
};

struct Connection
{
    bool canConnect;
    wchar_t characterName[20];
    bool otherPlayerExist;
    Location otherPlayerLocation;
    wchar_t otherCharacterName[20];
};

#pragma pack(pop)

#endif
