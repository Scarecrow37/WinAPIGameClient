#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>

#include "WindowsApplication.h"

#include "GameManager.h"
#include "Engine/World/World.h"
#include "Game/Functions/Initialize.h"
#include "InputSystems/Controller/Controller.h"
#include "InputSystems/Keyboad/Keyboard.h"
#include "InputSystems/Mouse/Mouse.h"
#include "Network/Network.h"
#include "RenderSystems/Renderer/WindowsGraphicDeviceInterface.h"
#include "TimeSystems/QueryClock/QueryClock.h"


int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WindowsApplication::Initialize(hInstance);
    if (!Network::isConnected) return EXIT_FAILURE;
    WindowsApplication::Run();
    WindowsApplication::Finalize();

    return EXIT_SUCCESS;
}

WindowsApplication* WindowsApplication::_instance = nullptr;

void WindowsApplication::Initialize(const HINSTANCE instanceHandle)
{
    WindowsApplication* windowsApplication = GetInstance();
    windowsApplication->_instanceHandle = instanceHandle;

    const TCHAR* applicationName = TEXT("Temp Name");

    WNDCLASS windowClass;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowsProcedure;
    windowClass.cbClsExtra = NULL;
    windowClass.cbWndExtra = NULL;
    windowClass.hInstance = instanceHandle;
    windowClass.hIcon = LoadIcon(instanceHandle, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(instanceHandle, IDC_ARROW);
    windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = applicationName;

    RegisterClass(&windowClass);

    RECT windowRectangle{
        ScreenStartLeft, ScreenStartTop, ScreenStartLeft + ScreenWidth, ScreenStartTop + ScreenHeight
    };
    AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

    int width = windowRectangle.right - windowRectangle.left;
    int height = windowRectangle.bottom - windowRectangle.top;

    GetInstance()->_windowHandle = CreateWindow(applicationName, applicationName, WS_OVERLAPPED | WS_SYSMENU,
                                                ScreenStartLeft, ScreenStartTop, width, height, NULL, NULL,
                                                instanceHandle, NULL);

    ShowWindow(GetInstance()->_windowHandle, SW_SHOWNORMAL);
    UpdateWindow(GetInstance()->_windowHandle);

    GetClientRect(GetInstance()->_windowHandle, &GetInstance()->_clientRectangle);


    // Network Prepare
    Network::Initialize();

    if (Network::isConnected)
    {
        // GameManager Prepare
        GameManager::SetKeyboardSystem(new Keyboard);
        GameManager::SetMouseSystem(new Mouse);
        GameManager::SetControllerSystem(new Controller);
        GameManager::SetTimeSystem(new QueryClock);
        GameManager::SetRenderer(new WindowsGraphicDeviceInterface);
        World* world = Game::LoadWorld(Network::connection);
        GameManager::SetWorld(world);
        GameManager::Initialize();
    }
}

void WindowsApplication::Run()
{
    GameManager::Run();
}

void WindowsApplication::Finalize()
{
    GameManager::Finalize();
}

HINSTANCE WindowsApplication::GetInstanceHandle()
{
    return GetInstance()->_instanceHandle;
}

HWND WindowsApplication::GetWindowHandle()
{
    return GetInstance()->_windowHandle;
}

int WindowsApplication::GetScreenWidth()
{
    return ScreenWidth;
}

int WindowsApplication::GetScreenHeight()
{
    return ScreenHeight;
}

int WindowsApplication::GetClientWidth()
{
    static int width = GetInstance()->_clientRectangle.right - GetInstance()->_clientRectangle.left;
    return width;
}

int WindowsApplication::GetClientHeight()
{
    static int height = GetInstance()->_clientRectangle.bottom - GetInstance()->_clientRectangle.top;
    return height;
}

void PlaceInCenterOfScreen(HWND windowHandle, DWORD style, DWORD exStyle)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    RECT clientRectangle;
    GetClientRect(windowHandle, &clientRectangle);

    int clientWidth = clientRectangle.right - clientRectangle.left;
    int clientHeight = clientRectangle.bottom - clientRectangle.top;

    SetWindowPos(windowHandle, nullptr, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2,
                 clientWidth, clientHeight, NULL);
}

LRESULT WindowsApplication::WindowsProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        PlaceInCenterOfScreen(windowHandle, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
    return 0;
}

WindowsApplication::WindowsApplication(): _instanceHandle(nullptr), _windowHandle(nullptr), _clientRectangle({})
{
}


WindowsApplication* WindowsApplication::GetInstance()
{
    if (_instance == nullptr) _instance = new WindowsApplication;
    return _instance;
}

void WindowsApplication::DestroyInstance()
{
    if (_instance == nullptr) return;
    delete _instance;
    _instance = nullptr;
}
