#pragma once

struct Connection;
class InputAction;
class Player;
class World;

namespace Game
{
    extern Player* player1;
    InputAction* CreateMovementAction();
    InputAction* CreateJumpAction();
    Player* CreatePlayer(const wchar_t* name);
    World* LoadWorld(const Connection& connection);
}
