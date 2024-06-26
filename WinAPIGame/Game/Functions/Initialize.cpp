﻿#include "Initialize.h"

#include "../../GameManager.h"
#include "../../Network/Packet.h"
#include "../../Engine/World/World.h"
#include "../Objects/Player.h"
#include "../../Engine/Object/Object.h"
#include "../../InputSystems/IInputSystem.h"
#include "../../InputSystems/Controller/Controller.h"
#include "../../InputSystems/EnhancedInputSystem/InputAction/InputAction.h"
#include "../../InputSystems/EnhancedInputSystem/Modifiers/Modifier.h"
#include "../../InputSystems/EnhancedInputSystem/Modifiers/ModifyStrategies/DirectionModifyStrategies/InverseDirectionModifyStrategy.h"
#include "../Objects/Floor.h"


namespace Game
{
    World* world = nullptr;
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    bool useController = false;

    InputAction* CreateMovementAction()
    {
        InputAction::Builder::GetInstance().Initialize().OpenInvokerSet();
        if (useController)
        {
            InputAction::Builder::GetInstance()
                .AddInvoker(GameManager::GetController()->GetInputValueGetter(Controller::Component::LeftThumbX));
        }
        else
        {
            InputAction::Builder::GetInstance()
                .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_LEFT), Modifier::InverseStrategy)
                .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_RIGHT));
        }
        InputAction* action = InputAction::Builder::GetInstance().CloseInvokerSet().Build();
        GameManager::AddInputAction(action);
        return action;
    }

    InputAction* CreateJumpAction()
    {
        InputAction::Builder::GetInstance().Initialize().OpenInvokerSet();
        if (useController)
        {
            InputAction::Builder::GetInstance()
                .AddInvoker(GameManager::GetController()->GetInputValueGetter(Controller::Component::B));
        }
        else
        {
            InputAction::Builder::GetInstance()
                .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_SPACE));
        }
        InputAction* jump = InputAction::Builder::GetInstance().CloseInvokerSet().Build();
        GameManager::AddInputAction(jump);
        return jump;
    }

    Player* CreatePlayer(const wchar_t* name)
    {
        player1 = new Player(name);
        player1->SetMovementAction(CreateMovementAction());
        player1->SetJumpAction(CreateJumpAction());
        return player1;
    }

    World* LoadWorld(const Connection& connection)
    {
        world = new World;
        world->AddObject(new Floor);

        world->AddObject(CreatePlayer(connection.characterName));
        if (connection.otherPlayerExist)
            MakeSecondPlayer(connection.otherCharacterName,
                             connection.otherPlayerLocation.x,
                             connection.otherPlayerLocation.y);
        return world;
    }

    void MakeSecondPlayer(const wchar_t* name, float x, float y)
    {
        player2 = new Player(name);
        player2->SetPosition({x, y});
        world->AddObject(player2);
    }

    void RemoveSecondPlayer()
    {
        world->RemoveObject(player2);
        delete player2;
        player2 = nullptr;
    }

    void UseController()
    {
        useController = true;
    }
}
