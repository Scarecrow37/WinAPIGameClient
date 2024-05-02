#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Packet.h"

#pragma comment(lib, "ws2_32")

int main()
{
    WSAData WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData);
    SOCKET ServerSocket = {};
    try
    {
        ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ServerSocket == INVALID_SOCKET)
        {
            throw std::exception("Server socket is invalid");
        }

        SOCKADDR_IN ServerAddress = {};
        ServerAddress.sin_family = AF_INET;
        int Result = inet_pton(AF_INET, "127.0.0.1", &ServerAddress.sin_addr);
        if (Result < 0)
        {
            throw std::exception("Ip address convert fail.");
        }
        ServerAddress.sin_port = htons(18080);
        Result = connect(ServerSocket, reinterpret_cast<SOCKADDR*>(&ServerAddress), sizeof(ServerAddress));
        if (Result < 0)
        {
            throw std::exception("Connect fail.");
        }

        HEADER Header = {};
        LOCATION Location = {};
        int Count = 0;

        // Receive Spawn Data
        int ReceiveByte = recv(ServerSocket, reinterpret_cast<char*>(&Header), sizeof(Header), MSG_WAITALL);
        if (ReceiveByte < 0)
        {
            throw std::exception("Receive fail.");
        }

        ReceiveByte = recv(ServerSocket, reinterpret_cast<char*>(&Location), sizeof(Location), MSG_WAITALL);
        if (ReceiveByte < 0)
        {
            throw std::exception("Receive fail.");
        }
        std::cout << "X : " << Location.X << std::endl << "Y : " << Location.Y << std::endl;

        while (Count < 100)
        {
            // Send Movement
            Header.Length = sizeof(MOVE);
            Header.Type = Type::Move;
            int SendByte = send(ServerSocket, reinterpret_cast<char*>(&Header), sizeof(Header), 0);
            if (SendByte < 0)
            {
                throw std::exception("Send fail.");
            }

            MOVE Move = {};
            Move.X = 1;
            Move.Y = 1;
            SendByte = send(ServerSocket, reinterpret_cast<char*>(&Move), sizeof(Move), 0);
            if (SendByte < 0)
            {
                throw std::exception("Send fail.");
            }

            // Response Location
            ReceiveByte = recv(ServerSocket, reinterpret_cast<char*>(&Header), sizeof(Header), MSG_WAITALL);
            if (ReceiveByte < 0)
            {
                throw std::exception("Receive fail.");
            }

            ReceiveByte = recv(ServerSocket, reinterpret_cast<char*>(&Location), sizeof(Location), MSG_WAITALL);
            if (ReceiveByte < 0)
            {
                throw std::exception("Receive fail.");
            }
            std::cout << "X : " << Location.X << std::endl << "Y : " << Location.Y << std::endl;
            ++Count;
        }
    }
    catch (std::exception& Exception)
    {
        std::cout << "[" << GetLastError() << "] " << Exception.what();

        closesocket(ServerSocket);
        WSACleanup();
        return -1;
    }

    closesocket(ServerSocket);
    WSACleanup();

    return 0;
}