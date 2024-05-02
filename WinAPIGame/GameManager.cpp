#include "GameManager.h"

#include <cassert>
#include <iostream>
#include <Windows.h>

#include "Engine/World/World.h"
#include "TimeSystems/ITimeSystem.h"
#include "InputSystems/IInputSystem.h"
#include "InputSystems/EnhancedInputSystem/InputAction/InputAction.h"
#include "RenderSystems/IRenderSystem.h"
#include "RenderSystems/RenderManager.h"
#include "RenderSystems/Renderer/IRenderer.h"
#include "CollisionSystem/CollisionManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager::~GameManager()
{
    delete _renderSystem;
}

void GameManager::SetTimeSystem(ITimeSystem* timeSystem)
{
    GetInstance()->_timeSystem = timeSystem;
}

void GameManager::SetInputSystem(const InputSystemType type, IInputSystem* inputSystem)
{
    GetInstance()->_inputSystems[type] = inputSystem;
}

void GameManager::SetMouseSystem(IInputSystem* mouse)
{
    GetInstance()->_inputSystems[Mouse] = mouse;
}

const IInputSystem* GameManager::GetMouse()
{
    return GetInstance()->_inputSystems[Mouse];
}

const IInputSystem* GameManager::GetKeyboard()
{
    return GetInstance()->_inputSystems[Keyboard];
}

const IInputSystem* GameManager::GetController()
{
    return GetInstance()->_inputSystems[Controller];
}

void GameManager::SetKeyboardSystem(IInputSystem* keyboard)
{
    GetInstance()->_inputSystems[Keyboard] = keyboard;
}

void GameManager::SetControllerSystem(IInputSystem* controller)
{
    GetInstance()->_inputSystems[Controller] = controller;
}

void GameManager::SetRenderer(IRenderer* renderer)
{
    GetInstance()->_renderSystem->SetRenderer(renderer);
}

void GameManager::AddInputAction(InputAction* inputAction)
{
    GetInstance()->_actions.PushBack(inputAction);
}

void GameManager::SetWorld(World* world)
{
    GetInstance()->_world = world;
}

IRenderSystem* GameManager::GetRenderSystem()
{
    return GetInstance()->_renderSystem;
}

GameManager* GameManager::GetInstance()
{
    if (_instance == nullptr) _instance = new GameManager;
    return _instance;
}

void GameManager::DestroyInstance()
{
    if (_instance == nullptr) return;
    delete _instance;
    _instance = nullptr;
}

IDeltaTime* GameManager::GetTime()
{
    return GetInstance()->_timeSystem;
}

IGetButtonState* GameManager::GetInput()
{
    // return GetInstance()->_inputSystem;
    return nullptr;
}

void GameManager::Initialize()
{
    GameManager* gameManager = GetInstance();
    for (const auto& inputSystem : gameManager->_inputSystems) inputSystem->Initialize();
    gameManager->_timeSystem->Initialize();
    gameManager->_renderSystem->Initialize();
    gameManager->Start();
}

void GameManager::Run()
{
    GameManager* gameManager = GetInstance();
    MSG windowMessage;
    while (gameManager->_isRunning)
    {
        if (PeekMessage(&windowMessage, nullptr, NULL, NULL, PM_REMOVE))
        {
            switch (windowMessage.message)
            {
            case WM_QUIT:
                gameManager->Stop();
                break;
            case WM_KEYDOWN:
                // gameManager->_inputSystem->KeyDown(static_cast<char>(windowMessage.wParam));
                break;
            case WM_KEYUP:
                // gameManager->_inputSystem->KeyUp(static_cast<char>(windowMessage.wParam));
                break;
            default:
                DispatchMessage(&windowMessage);
                break;
            }
        }
        else
        {
            gameManager->FixedUpdate();
            gameManager->Update();
            gameManager->Render();
        }
    }
}

void GameManager::Finalize()
{
    GetInstance()->_renderSystem->Finalize();
}


void GameManager::Update() const
{
    _timeSystem->Update();
    for (const auto& inputSystem : _inputSystems) inputSystem->Update();
    for (const auto& action : _actions) action->Update();
    _world->Update(_timeSystem->GetDeltaTime());
    for (const auto& inputSystem : _inputSystems) inputSystem->Reset();
}

void GameManager::FixedUpdate() const
{
    static float elapsedTime;
    elapsedTime += _timeSystem->GetDeltaTime();
    while (elapsedTime >= _fixedUpdateInterval)
    {
        _collisionManager->CollisionUpdate(_world->GetCollisions());
        _world->FixedUpdate();
        elapsedTime -= _fixedUpdateInterval;
    }
}

void GameManager::Render() const
{
    _renderSystem->GetRenderer()->BeginDraw();
    _world->Render(_renderSystem);
    _renderSystem->GetRenderer()->EndDraw();
}

GameManager::GameManager(): _timeSystem(nullptr), _inputSystems{}, _renderSystem(new RenderManager),
                            _collisionManager(new CollisionManager), _world(nullptr), _isRunning(false),
                            _fixedUpdateInterval(0.02f)
{
}

void GameManager::Start()
{
    _isRunning = true;
}

void GameManager::Stop()
{
    _isRunning = false;
}
