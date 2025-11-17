//
// main.cpp
//

#include "stdafx.h"
#include ".\Resources\resource.h"

#include "SceneManagement.h"
#include "InputSystem.h"
#include "HEToolKit\heRawGamepad.h"

#define HE_KEYBOARD   1
#define HE_MOUSE      0
#define HE_GAMEPAD    1
#define HE_FULLSCREEN 0
enum class Screen : int {
    Width = 1280,
    Height = 720
};
static const WCHAR* TITLE = L"HuGame";

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable(Helper)
SceneManagement               SceneManager;
HE::Scene3D::Scene&           DefaultScene =  wi::scene::GetScene();
HE::Scene3D::CameraComponent* MainCamera   = &wi::scene::GetCamera();
HE::RenderPath2D*             RenderingPath;

#if HE_KEYBOARD
static std::unique_ptr<DirectX::Keyboard> keyboard;
#endif
#if HE_MOUSE
static std::unique_ptr<DirectX::Mouse> mouse;
#endif
INPUTSYSTEM InputSystem;

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;

    // TODO: Place code here.

    BOOL dpi_success = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    assert(dpi_success);

    wi::arguments::Parse(lpCmdLine); // if you wish to use command line arguments, here is a good place to parse them...

    //constexpr int MAX_LOADSTRING = 100;
    //WCHAR title[MAX_LOADSTRING];
    //LoadStringW(hInstance, IDS_APP_TITLE, title, MAX_LOADSTRING);
    //WCHAR window_class[MAX_LOADSTRING];
    //LoadStringW(hInstance, IDC_HSGAMEENGINE, window_class, MAX_LOADSTRING);

    // Register class and create window
    {
        // Register class
        WNDCLASSEXW wcex{};
        wcex.cbSize        = sizeof(wcex);
        wcex.style         = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc   = WndProc;
        wcex.hInstance     = hInstance;
        wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HUNYAN));
        wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszClassName = MAKEINTRESOURCEW(IDC_HUGAME);
        wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_HUNYAN));
        if (!RegisterClassExW(&wcex))
            return 1;

        // Create window
        RECT rc{ 0, 0, static_cast<LONG>(Screen::Width), static_cast<LONG>(Screen::Height) };

#if !HE_FULLSCREEN
        AdjustWindowRect(&rc, WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX, FALSE);

        const int  kScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
        const int  kScreenHeight = GetSystemMetrics(SM_CYSCREEN);

        const long kWndWidth  = rc.right  - rc.left;
        const long kWndHeight = rc.bottom - rc.top;

        const int  kWndPosX = (kScreenWidth  - kWndWidth ) / 2;
        const int  kWndPosY = (kScreenHeight - kWndHeight) / 2;

        HWND hwnd = CreateWindowExW(0, wcex.lpszClassName, TITLE,
            WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX,
            kWndPosX, kWndPosY, kWndWidth, kWndHeight, nullptr, nullptr, hInstance,
            nullptr);
        // TODO: Change to CreateWindowExW(WS_EX_TOPMOST, L"HSGEngine_WindowClass", L"HumanSendai GameEngine", WS_POPUP,
        // to default to fullscreen.

        if (!hwnd)
            return 1;

        ShowWindow(hwnd, nCmdShow);
        // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.
#else
        HWND hwnd = CreateWindowExW(
            WS_EX_TOPMOST, wcex.lpszClassName, TITLE,
            WS_POPUP | WS_SYSMENU,
            0, 0, 0, 0, nullptr, nullptr, hInstance,
            nullptr
        );
        if (!hwnd)
            return 1;

        SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
#endif

        wi::Timer timer;
#if HE_KEYBOARD
        keyboard = std::make_unique<DirectX::Keyboard>();
#endif
#if HE_MOUSE
        mouse = std::make_unique<Mouse>();
        mouse->SetWindow(hwnd);
        InputSystem.Mouse.mouse = mouse.get();
#endif
#if HE_GAMEPAD
        he::gamepad::Initialize();
#endif
        wi::backlog::post("InputSystem Initialized (" + std::to_string((int)std::round(timer.elapsed())) + " ms)");
    }

    // Main message loop
    //MSG msg{};
    //while (WM_QUIT != msg.message)
    //{
    //    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //    else
    //    {
    //        SceneManager.Run();
    //        SceneManager.TransitionScene();
    //    }
    //}
    //return static_cast<int>(msg.wParam);

    MSG msg{};
    while (true) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				return static_cast<int>(msg.wParam);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

#if HE_KEYBOARD
        InputSystem.Keyboard.isPressed = keyboard->GetState();
        InputSystem.Keyboard.tracker.Update(InputSystem.Keyboard.isPressed);
#endif
#if HE_MOUSE
        InputSystem.Mouse.isPressed = mouse->GetState();
        InputSystem.Mouse.was.Update(InputSystem.Mouse.isPressed);
#endif
#if HE_GAMEPAD
        he::gamepad::Update();
#endif

		SceneManager.Run();
		SceneManager.TransitionScene();
	}

    return 0;
}

// Windows procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#if !HE_FULLSCREEN
    static bool s_fullscreen = false;

#else
     // TODO: Set s_fullscreen to true if defaulting to fullscreen.
    static bool s_fullscreen = true;
#endif

    switch (message)
    {
#if defined(HE_KEYBOARD) || defined(HE_MOUSE)
    case WM_ACTIVATE:
#if HE_KEYBOARD
        DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
#endif
#if HE_MOUSE
        Mouse::ProcessMessage(message, wParam, lParam);
#endif
        return 0;
#endif

#if HE_KEYBOARD || HE_MOUSE
    case WM_ACTIVATEAPP:
#if HE_KEYBOARD
        DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
#endif
#if HE_MOUSE
        Mouse::ProcessMessage(message, wParam, lParam);
#endif
#if HE_KEYBOARD
        if (wParam) {
            InputSystem.Keyboard.tracker.Reset();
        }
#endif
        return 0;
#endif

    case WM_SIZE:
    case WM_DPICHANGED:
        if (SceneManager.is_window_active) {
            SceneManager.SetWindow(hWnd);

            RECT rect;
            GetClientRect(hWnd, &rect);
            if (Screen::Width >= Screen::Height)
                SceneManager.canvas.dpi = float(96.0 * (rect.right - rect.left) / (int)Screen::Width);
            else
                SceneManager.canvas.dpi = float(96.0 * (rect.bottom - rect.top) / (int)Screen::Height);
        }
        return 0;

    case WM_CHAR:
        switch (wParam)
        {
        case VK_BACK:
            wi::gui::TextInputField::DeleteFromInput();
            break;
        case VK_RETURN:
            break;
        case VK_ESCAPE:
//#ifdef _DEBUG
            PostMessage(hWnd, WM_CLOSE, 0, 0);
//#endif
            break;
        default:
        {
            const wchar_t c = (const wchar_t)wParam;
            wi::gui::TextInputField::AddInput(c);
        }
        break;
        }
        return 0;

#if HE_MOUSE || HE_GAMEPAD
    case WM_INPUT:
#if HE_MOUSE
        Mouse::ProcessMessage(message, wParam, lParam);
#endif
#if HE_GAMEPAD
        he::rawgamepad::ParseMessage((void*)lParam);
#endif
        return 0;
#endif

    case WM_KILLFOCUS:
        SceneManager.is_window_active = false;
        return 0;

    case WM_SETFOCUS:
        SceneManager.is_window_active = true;
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    return 0;

    case WM_GETMINMAXINFO:
        if (lParam)
        {
            auto info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = 320;
            info->ptMinTrackSize.y = 180;
        }
        return 0;

    case WM_POWERBROADCAST:
        switch (wParam)
        {
        case PBT_APMQUERYSUSPEND:
            SceneManager.is_window_active = false;
            return TRUE;

        case PBT_APMRESUMESUSPEND:
            SceneManager.is_window_active = true;
            return TRUE;
        }
        break;

    case WM_CLOSE:
        //wi::initializer::WaitForInitializeFinished();
        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        wi::jobsystem::ShutDown();
        PostQuitMessage(0);
        return 0;

#if HE_KEYBOARD
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
        return 0;
#endif

    case WM_SYSKEYDOWN:
#if HE_KEYBOARD
        DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
#endif
        if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
        {
            // Implements the classic ALT+ENTER fullscreen toggle
            if (s_fullscreen)
            {
                constexpr DWORD WND_STYLE = WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX;
                SetWindowLongPtr(hWnd, GWL_STYLE, WND_STYLE);
                SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

                RECT rc = { 0, 0, static_cast<LONG>(Screen::Width), static_cast<LONG>(Screen::Height) };
                AdjustWindowRect(&rc, WND_STYLE, FALSE);

                HDC hdc = GetDC(hWnd);
                const int  kScreenWidth  = GetDeviceCaps(hdc, HORZRES);
                const int  kScreenHeight = GetDeviceCaps(hdc, VERTRES);
                ReleaseDC(hWnd, hdc);

                // const int  kScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
                // const int  kScreenHeight = GetSystemMetrics(SM_CYSCREEN);

                const long kWndWidth  = rc.right  - rc.left;
                const long kWndHeight = rc.bottom - rc.top;

                const int  kWndPosX = (kScreenWidth  - kWndWidth ) / 2;
                const int  kWndPosY = (kScreenHeight - kWndHeight) / 2;

                ShowWindow(hWnd, SW_SHOWNORMAL);

                SetWindowPos(
                    hWnd, HWND_TOP, kWndPosX, kWndPosY, kWndWidth, kWndHeight,
                    SWP_NOZORDER | SWP_FRAMECHANGED
                );
            }
            else
            {
                SetWindowLongPtr(hWnd, GWL_STYLE, 0);
                SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

                SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                ShowWindow(hWnd, SW_SHOWMAXIMIZED);
            }

            s_fullscreen = !s_fullscreen;
        }
        return 0;

#if HE_MOUSE
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEHOVER:
        Mouse::ProcessMessage(message, wParam, lParam);
        return 0;
#endif

    case WM_CAPTURECHANGED:
        SceneManager.OnCaptureChanged();
        return 0;

    //case WM_MENUCHAR:
    //    // A menu is active and the user presses a key that does not correspond
    //    // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
    //    return MAKELRESULT(0, MNC_CLOSE);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
