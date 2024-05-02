#pragma once
#include <Windows.h>

class WindowsApplication final
{
    static constexpr int ScreenStartLeft = 10;
    static constexpr int ScreenStartTop = 10;
    static constexpr int ScreenWidth = 1024;
    static constexpr int ScreenHeight = 768;

public:
    WindowsApplication(const WindowsApplication& other) = delete;
    WindowsApplication(WindowsApplication&& other) noexcept = delete;
    WindowsApplication& operator=(const WindowsApplication& other) = delete;
    WindowsApplication& operator=(WindowsApplication&& other) noexcept = delete;
    ~WindowsApplication() = default;

    static void Initialize(HINSTANCE instanceHandle);
    static void Run();
    static void Finalize();

    static HINSTANCE GetInstanceHandle();
    static HWND GetWindowHandle();

    static int GetScreenWidth();
    static int GetScreenHeight();

    static int GetClientWidth();
    static int GetClientHeight();

    static LRESULT CALLBACK WindowsProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

private:
    WindowsApplication();

    static WindowsApplication* GetInstance();
    static void DestroyInstance();

    static WindowsApplication* _instance;

    HINSTANCE _instanceHandle;
    HWND _windowHandle;
    RECT _clientRectangle;
};
