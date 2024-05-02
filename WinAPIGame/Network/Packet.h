#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

enum Type
{
    Connect = 10,
    OtherConnect = 11,
    Disconnect = 20,
    PlayerLocation = 30,
    OtherLocation = 31,
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

struct OtherConnection
{
    wchar_t characterName[20];
    Location playerLocation;
};

#pragma pack(pop)

#endif
