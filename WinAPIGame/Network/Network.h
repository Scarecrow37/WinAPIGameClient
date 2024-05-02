#pragma once
#include <winsock2.h>
#include "Packet.h"

namespace Network
{
    extern SOCKET serverSocket;
    extern bool isConnected;
    extern Connection connection;
    void Initialize();
    void Receive();
    void Send();
    void Finalize();
}
