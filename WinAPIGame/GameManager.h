#pragma once
#include "Containers/Vector.h"

class CollisionManager;class IRenderer;
class IRenderSystem;
class InputAction;
class World;
class IGetButtonState;
class IInputSystem;
class IDeltaTime;
class ITimeSystem;

class GameManager
{
    enum InputSystemType
    {
        Mouse,
        Keyboard,
        Controller,
        Max
    };

public:
    GameManager(const GameManager& other) = delete;
    GameManager(GameManager&& other) noexcept = delete;
    GameManager& operator=(const GameManager& other) = delete;
    GameManager& operator=(GameManager&& other) noexcept = delete;
    ~GameManager();

    static void SetTimeSystem(ITimeSystem* timeSystem);
    static void SetInputSystem(InputSystemType type, IInputSystem* inputSystem);
    static void SetMouseSystem(IInputSystem* mouse);
    static const IInputSystem* GetMouse();
    static void SetKeyboardSystem(IInputSystem* keyboard);
    static const IInputSystem* GetKeyboard();
    static void SetControllerSystem(IInputSystem* controller);
    static const IInputSystem* GetController();
    static void SetRenderer(IRenderer* renderer);
    static void AddInputAction(InputAction* inputAction);
    static void SetWorld(World* world);
    static IRenderSystem* GetRenderSystem();

    static GameManager* GetInstance();
    static void DestroyInstance();
    static IDeltaTime* GetTime();
    static IGetButtonState* GetInput();

    static void Initialize();
    static void Run();
    static void Finalize();

private:
    GameManager();

    void Start();
    void Stop();
    void Update() const;
    void FixedUpdate() const;
    void Render() const;

    static GameManager* _instance;

    ITimeSystem* _timeSystem;
    IInputSystem* _inputSystems[Max];
    IRenderSystem* _renderSystem;
    CollisionManager* _collisionManager;

    Dosuha::Vector<InputAction*> _actions;

    World* _world;

    bool _isRunning;
    float _fixedUpdateInterval;
};
