﻿#include "Initialize.h"

#include "../../GameManager.h"
#include "../../Packet.h"
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
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    InputAction* CreateMovementAction()
    {
        InputAction* action = InputAction::Builder::GetInstance()
                              .Initialize()
                              .OpenInvokerSet()
                              .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_LEFT),
                                          Modifier::InverseStrategy)
                              .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_RIGHT))
                              .CloseInvokerSet()
                              .OpenInvokerSet()
                              .AddInvoker(
                                  GameManager::GetController()->GetInputValueGetter(Controller::Component::LeftThumbX))
                              .CloseInvokerSet()
                              .Build();
        GameManager::AddInputAction(action);
        return action;
    }

    InputAction* CreateJumpAction()
    {
        InputAction* jump = InputAction::Builder::GetInstance()
                            .Initialize()
                            .OpenInvokerSet()
                            .AddInvoker(GameManager::GetKeyboard()->GetInputValueGetter(VK_SPACE))
                            .CloseInvokerSet()
                            .OpenInvokerSet()
                            .AddInvoker(GameManager::GetController()->GetInputValueGetter(Controller::Component::A))
                            .CloseInvokerSet()
                            .Build();
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
        World* world = new World;
        world->AddObject(new Floor);

        world->AddObject(CreatePlayer(connection.characterName));
        if (connection.otherPlayerExist)
        {
            player2 = new Player(connection.otherCharacterName);
            player2->SetPosition({connection.otherPlayerLocation.x, connection.otherPlayerLocation.y});
            world->AddObject(player2);
        }
        return world;
    }
}