#pragma once

struct Connection;
class InputAction;
class Player;
class World;

namespace Game
{
    extern World* world;
    extern Player* player1;
    extern Player* player2;
    InputAction* CreateMovementAction();
    InputAction* CreateJumpAction();
    Player* CreatePlayer(const wchar_t* name);
    World* LoadWorld(const Connection& connection);
    void MakeSecondPlayer(const wchar_t* name, float x = 0, float y = 0);
    void RemoveSecondPlayer();
}
