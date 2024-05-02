#include "Network.h"
#include <iostream>
#include <WS2tcpip.h>

#include "../Game/Functions/Initialize.h"
#include "../Game/Objects/Player.h"

#pragma comment(lib,"ws2_32")

namespace Network
{
    SOCKET serverSocket = {};
    bool isConnected = true;
    Connection connection = {};

    void Initialize()
    {
        WSAData wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        try
        {
            serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (serverSocket == INVALID_SOCKET) throw std::exception("Server socket is invalid.");
            SOCKADDR_IN serverAddress = {};
            serverAddress.sin_family = AF_INET;
            int result = inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
            if (result < 0) throw std::exception("IP address convert fail.");
            serverAddress.sin_port = htons(18080);
            result = connect(serverSocket, reinterpret_cast<SOCKADDR*>(&serverAddress), sizeof(serverAddress));
            if (result < 0) throw std::exception("Connect fail");

            // Connect Sequence
            Header header = {};
            int receiveByte = recv(serverSocket, reinterpret_cast<char*>(&header), sizeof(header), MSG_WAITALL);
            if (receiveByte < 0 || header.type != Connect) throw std::exception("Connection header receive fail.");
            receiveByte = recv(serverSocket, reinterpret_cast<char*>(&connection), header.length, MSG_WAITALL);
            if (receiveByte < 0) throw std::exception("Connection data receive fail.");
            if (!connection.canConnect) throw std::exception("Server is full.");
        }
        catch (const std::exception& exception)
        {
            isConnected = false;
            const int length = static_cast<int>(strlen(exception.what())) + 1;
            wchar_t* buffer = new wchar_t[length];
            MultiByteToWideChar(CP_ACP, 0, exception.what(), length, buffer, length);
            MessageBox(nullptr, buffer, L"연결 실패", MB_OK);
            Finalize();
        }
    }

    void SetSocketToNonBlocking()
    {
        u_long iMode = 1;
        if (const int result = ioctlsocket(serverSocket, FIONBIO, &iMode); result < 0)
            throw std::exception(
                "It is fail to make socket non-blocking.");
    }

    void SetSocketToBlocking()
    {
        u_long iMode = 0;
        if (const int result = ioctlsocket(serverSocket, FIONBIO, &iMode); result < 0)
            throw std::exception(
                "It is fail to make socket blocking.");
    }

    void Receive()
    {
        SetSocketToNonBlocking();
        Header header = {};
        int receiveByte = recv(serverSocket, reinterpret_cast<char*>(&header), sizeof(header), 0);
        if (receiveByte == 0) throw std::exception("Disconnect");
        if (receiveByte > 0)
        {
            SetSocketToBlocking();
            switch (header.type)
            {
            case OtherConnect:
                {
                    OtherConnection otherConnection = {};
                    receiveByte = recv(serverSocket, reinterpret_cast<char*>(&otherConnection), header.length,
                                       MSG_WAITALL);
                    if (receiveByte <= 0) throw std::exception("Receive other connection data fail.");
                    Game::MakeSecondPlayer(otherConnection.characterName, otherConnection.playerLocation.x,
                                           otherConnection.playerLocation.y);
                }
                break;
            case Disconnect:
                {
                    Game::RemoveSecondPlayer();
                }
                break;
            case OtherLocation:
                {
                    Location location = {};
                    receiveByte = recv(serverSocket, reinterpret_cast<char*>(&location), header.length, MSG_WAITALL);
                    if (receiveByte <= 0) throw std::exception("Receive other location data fail.");
                    Game::player2->SetPosition({location.x, location.y});
                }
                break;
            default:
                throw std::exception("Receive unknown packet.");
            }
        }
    }

    void Send()
    {
        Header header = {};
        header.type = PlayerLocation;
        header.length = sizeof(Location);
        int result = send(serverSocket, reinterpret_cast<char*>(&header), sizeof(header), 0);
        if (result < 0) throw std::exception("Player location header send fail.");
        Location location = {};
        location.x = Game::player1->GetTransform().location.x;
        location.y = Game::player1->GetTransform().location.y;
        result = send(serverSocket, reinterpret_cast<char*>(&location), sizeof(location), 0);
        if (result < 0) throw std::exception("Player location data send fail.");
    }

    void Finalize()
    {
        closesocket(serverSocket);
        WSACleanup();
    }
}
