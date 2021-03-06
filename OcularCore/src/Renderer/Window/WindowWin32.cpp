/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Exceptions/Exception.hpp"
#include "Renderer/Window/WindowWin32.hpp"
#include "OcularEngine.hpp"
#include "Events/Events/ShutdownEvent.hpp"
#include "Events/Events/WindowResizeEvent.hpp"
#include "Time/Timer.hpp"
#include "Utilities/StringComposer.hpp"

#include <sstream>
#include <bitset>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // NON-CLASS METHODS
        //----------------------------------------------------------------------------------

        LRESULT CALLBACK WndProc(HWND const hwnd, UINT const msg, WPARAM const wp, LPARAM const lp)
        {
            WindowWin32* window = (WindowWin32*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if(window != nullptr)
            {
                return window->processMessage(hwnd, msg, wp, lp);
            }
            else 
            {
                return DefWindowProc(hwnd, msg, wp, lp);
            }
        }

        DWORD CreateWindowStyle(WindowDisplayMode const display)
        {
            switch(display)
            {
            case WindowDisplayMode::WindowedBorderless:
                return WS_POPUP | WS_VISIBLE;

            case WindowDisplayMode::FullscreenBordered:
                return WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_VISIBLE;

            case WindowDisplayMode::FullscreenBorderless:
                return WS_POPUP | WS_MAXIMIZE | WS_VISIBLE;

            case WindowDisplayMode::WindowedBordered:
            default:
                return WS_OVERLAPPEDWINDOW | WS_VISIBLE;
            }
        }

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        WindowWin32::WindowWin32(WindowDescriptor const& descriptor)
            : AWindow(descriptor), 
              m_HINSTANCE(nullptr), 
              m_HWND(nullptr)
        {
            ZeroMemory(&m_RawDevices[0], sizeof(RAWINPUTDEVICE));
            ZeroMemory(&m_RawDevices[1], sizeof(RAWINPUTDEVICE));
        }

        WindowWin32::WindowWin32(WindowDescriptor const& descriptor, void* windowID)
            : AWindow(descriptor), 
              m_HINSTANCE(nullptr), 
              m_HWND((HWND)(windowID))
        {
            ZeroMemory(&m_RawDevices[0], sizeof(RAWINPUTDEVICE));
            ZeroMemory(&m_RawDevices[1], sizeof(RAWINPUTDEVICE));
        }

        WindowWin32::~WindowWin32() 
        {
            if((m_HWND != nullptr) && (m_Descriptor.external == false))
            {
                DestroyWindow(m_HWND);
                UnregisterClass(TEXT(m_Name.c_str()), m_HINSTANCE);

                m_HWND = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void WindowWin32::showCursor(bool show)
        {
            if(show)
            {
                while(ShowCursor(true) < 0);
            }
            else
            {
                while(ShowCursor(false) >= 0);
            }
        }

        HWND WindowWin32::getHWND() const
        {
            return m_HWND;
        }

        HINSTANCE WindowWin32::getHINSTANCE() const 
        {
            return m_HINSTANCE;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void WindowWin32::open()
        {
            if(m_HWND == nullptr)
            {
                m_HINSTANCE = GetModuleHandle(NULL);

                if(m_HINSTANCE == nullptr)
                {
                    const DWORD error = GetLastError();
                    THROW_EXCEPTION(OCULAR_STRING_COMPOSER("Failed to get HINSTANCE [WinApi error ", error, "]"));
                }

                RECT windowRect = createWindowRect();
                WNDCLASS windowClass = createWndClass((WNDPROC)WndProc);

                RegisterClass(&windowClass);

                if(!m_Descriptor.exclusiveMode) {
                    m_HWND = CreateWindow(TEXT(m_Descriptor.displayName.c_str()),
                                          TEXT(m_Descriptor.displayName.c_str()),
                                          CreateWindowStyle(m_Descriptor.displayMode),
                                          CW_USEDEFAULT,
                                          0,
                                          windowRect.right,
                                          windowRect.bottom,
                                          0,
                                          0,
                                          m_HINSTANCE,
                                          this);
                } 
                else 
                {
                    m_HWND = CreateWindowEx(WS_EX_TOPMOST,
                                            TEXT(m_Descriptor.displayName.c_str()),
                                            TEXT(m_Descriptor.displayName.c_str()),
                                            CreateWindowStyle(m_Descriptor.displayMode),
                                            CW_USEDEFAULT,
                                            0,
                                            CW_USEDEFAULT,
                                            0,
                                            0,
                                            0,
                                            m_HINSTANCE,
                                            this);
                }

                if(m_HWND == nullptr) 
                {
                    const DWORD error = GetLastError();
                    std::stringstream stream;
                    stream << "Failed to create window [WinApi error " << error << "]";

                    THROW_EXCEPTION(stream.str());
                }

                m_OSPointer = (void*)(m_HWND);

                // Setup our window to be later retrieved by WndProc
                // TODO: Will this cause errors with multiple windows? Need a different ID (GWLP_USERDATA - Window #)?
                SetWindowLongPtr(m_HWND, GWLP_USERDATA, (LONG_PTR)this);

                // Show the window
                ShowWindow(m_HWND, SW_SHOW);
                UpdateWindow(m_HWND);

                SetForegroundWindow(m_HWND);
                SetFocus(m_HWND);

                registerRawInput();
            }
            else if(m_HINSTANCE == nullptr)
            {
                // We were provided a window handle already
                connect();
            }
        }
        
        void WindowWin32::connect()
        {
             m_HINSTANCE = GetModuleHandle(NULL);

            if(m_HINSTANCE == nullptr)
            {
                const DWORD error = GetLastError();
                THROW_EXCEPTION(OCULAR_STRING_COMPOSER("Failed to get HINSTANCE [WinApi error ", error, "]"));
            }

            if(IsWindow(m_HWND))
            {
                m_OSPointer = (void*)(m_HWND);

                RECT rect;

                if(GetWindowRect(m_HWND, &rect) == TRUE)
                {
                    m_Descriptor.width = rect.right;
                    m_Descriptor.height = rect.bottom;
                }
                else
                {
                    THROW_EXCEPTION("Failed to retrieve Window Rect");
                }
            }
            else
            {
                THROW_EXCEPTION("Invalid HWND Provided");
            }
        }

        void WindowWin32::update(uint64_t const time)
        {
            MSG message;
            BOOL retVal;

            while((retVal = PeekMessage(&message, 0, 0, 0, PM_REMOVE)) != 0)
            {
                if(retVal != -1)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                else
                {
                    OcularLogger->error("Unexpected error occurred while processing system messages", OCULAR_INTERNAL_LOG("WindowWin32", "update"));
                }
            }
        }

        void WindowWin32::close()
        {
            if(m_HWND != nullptr)
            {
                if(!DestroyWindow(m_HWND))
                {
                    const DWORD error = GetLastError();
                    std::stringstream stream;
                    stream << "Failed to destroy window handle '" << m_HWND
                           << "' [WinApi error " << error << "]";

                    THROW_EXCEPTION(stream.str());
                }

                m_HWND = nullptr;
            }

            if(!UnregisterClass(TEXT(m_Name.c_str()), m_HINSTANCE))
            {
                const DWORD error = GetLastError();
                std::stringstream stream;
                stream << "Failed to unregister class '" << m_Name 
                       << "' [WinApi error " << error << "]";

                THROW_EXCEPTION(stream.str());
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        RECT WindowWin32::createWindowRect()
        {
            RECT windowRect;

            windowRect.left   = 0L;
            windowRect.right  = static_cast<long>(m_Descriptor.width);
            windowRect.top    = 0L;
            windowRect.bottom = static_cast<long>(m_Descriptor.height);

            return windowRect;
        }

        WNDCLASS WindowWin32::createWndClass(WNDPROC const wndProc)
        {
            WNDCLASS windowClass;

            windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            windowClass.lpfnWndProc   = wndProc;
            windowClass.cbClsExtra    = 0;
            windowClass.cbWndExtra    = sizeof(WindowWin32*);
            windowClass.hInstance     = m_HINSTANCE;
            windowClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO); // TODO
            windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);   // TODO
            windowClass.hbrBackground = NULL;
            windowClass.lpszMenuName  = NULL;
            windowClass.lpszClassName = TEXT(m_Name.c_str());

            return windowClass;
        }

        LRESULT CALLBACK WindowWin32::processMessage(HWND const hWnd, UINT const uMsg, WPARAM const wParam, LPARAM const lParam)
        {
            LRESULT result = 0;

            switch(uMsg)
            {
            case WM_DESTROY:
            case WM_CLOSE:
            case WM_QUIT:
                OcularEngine.EventManager()->queueEvent(std::make_shared<ShutdownEvent>());
                break;

            case WM_SIZE:
            {
                const uint32_t width  = static_cast<uint32_t>(LOWORD(lParam));
                const uint32_t height = static_cast<uint32_t>(HIWORD(lParam));

                OcularEngine.EventManager()->queueEvent(std::make_shared<WindowResizeEvent>(this, width, height));

                break;
            }

            case WM_INPUT:
            {
                char buffer[sizeof(RAWINPUT)];
                uint32_t size = sizeof(RAWINPUT);

                if(GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER)) != -1)
                {
                    RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);

                    if(raw->header.dwType == RIM_TYPEKEYBOARD)
                    {
                        handleRawKeyboardInput(raw->data.keyboard);
                    }
                    else if(raw->header.dwType == RIM_TYPEMOUSE)
                    {
                        handleRawMouseInput(raw->data.mouse);
                    }
                }
                else
                {
                    const DWORD error = GetLastError();
                    OcularLogger->warning("Failed to get raw input data [WinApi error ", error, "]",
                                          OCULAR_INTERNAL_LOG("WindowWin32", "processMessage"));
                }

                break;
            }

            default:
                result = DefWindowProc(hWnd, uMsg, wParam, lParam);
                break;
            }

            return result;
        }

        void WindowWin32::registerRawInput()
        {
            /**
             * Raw Input Introduction: https://msdn.microsoft.com/en-us/library/ms645546(v=vs.85).aspx
             * Raw Input Usage Pages:  http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
             *
             * Brief extract of the above PDF incase it goes down (been several revisions and deadlinks):
             *
             * | Page ID |        Page Name         |
             * | :-----: | :----------------------: |
             * |   00    |        Undefined         |
             * |   01    | Generic Desktop Controls |
             * |   02    |    Simulation Controls   |
             * |   03    |       VR Controls        |
             * |   04    |      Sport Controls      |
             * |   05    |       Game Controls      |
             * |   06    |  Generic Device Controls |
             * |   07    |     Keyboard / Keypad    |
             * |   08    |           LEDs           |
             * |   09    |          Button          |
             *
             * We are primarily interested in the 'Generic Desktop Controls' page:
             *
             * | Usage ID |      Usage Name       |
             * | :------: | :-------------------: |
             * |    00    |      Undefined        |
             * |    01    |       Pointer         |
             * |    02    |        Mouse          |
             * |    03    |       Reserved        |
             * |    04    |       Joystick        |
             * |    05    |       Game Pad        |
             * |    06    |       Keyboard        |
             * |    07    |        Keypad         |
             * |    08    | Multi-axis Controller |
             */

            // Register for keyboard messages

            // NOTE: Using the RIDEV_NOLEGACY flag causes the application to 'block':
            // Window resize, close, move, etc. events are not processed and the cursor
            // is just the busy icon (spinning doughnut). Need to look into why this is
            // and/or if RIDEV_NOLEGACY is actually needed at all.

            m_RawDevices[0].usUsagePage = 0x01;
            m_RawDevices[0].usUsage     = 0x06;
            m_RawDevices[0].dwFlags     = 0;// RIDEV_NOLEGACY;   // Add HID keyboard and ignore legacy keyboard messages
            m_RawDevices[0].hwndTarget  = m_HWND;                // Target only this window. We do not care about messages that are out of focus.

            // Register for mouse messages

            m_RawDevices[1].usUsagePage = 0x01;
            m_RawDevices[1].usUsage     = 0x02;
            m_RawDevices[1].dwFlags     = 0;// RIDEV_NOLEGACY;
            m_RawDevices[1].hwndTarget  = m_HWND;

            if(RegisterRawInputDevices(m_RawDevices, 2, sizeof(m_RawDevices[0])) == FALSE)
            {
                const DWORD error = GetLastError();
                OcularLogger->error("Failed to register for raw input devices [WinApi error ", error, "]", 
                                    OCULAR_INTERNAL_LOG("WindowWin32", "registerRawInput"));
            }
        }

        void WindowWin32::handleRawKeyboardInput(RAWKEYBOARD const& data)
        {
            // http://blog.molecular-matters.com/2011/09/05/properly-handling-keyboard-input/#more-143
            // Helped with the trickier key strokes

            uint32_t virtualKey = data.VKey;
            uint32_t scanCode = data.MakeCode;
            uint32_t flags = data.Flags;

            if(virtualKey != 255)
            {
                if(virtualKey == VK_SHIFT)
                {
                    // Use MapVirtualKey to map to left or right shift
                    virtualKey = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
                }
                else if(virtualKey == VK_NUMLOCK)
                {
                    // Numlock sends the same scancode as pause/break; Handle that.
                    scanCode = (MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC) | 0x100);
                }

                //--------------------------------------------------------
                // Check for special escape sequences
                // http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html

                const bool isE0 = ((flags & RI_KEY_E0) != 0);
                const bool isE1 = ((flags & RI_KEY_E1) != 0);

                if(isE1)
                {
                    if(virtualKey == VK_PAUSE)
                    {
                        scanCode = 0x45;
                    }
                    else
                    {
                        scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
                    }
                }

                //--------------------------------------------------------
                // Get the actual key that was pressed/released

                KeyboardKeys key = KeyboardKeys::Undefined;

                switch(virtualKey)
                {
                    //------------------------------------
                    // Shift, Ctrl, Alt

                case VK_LSHIFT:
                    key = KeyboardKeys::ShiftLeft;
                    break;

                case VK_RSHIFT:
                    key = KeyboardKeys::ShiftRight;
                    break;

                case VK_CONTROL:
                    key = (isE0 ? KeyboardKeys::CtrlRight : KeyboardKeys::CtrlLeft);
                    break;

                case VK_MENU:
                    key = (isE0 ? KeyboardKeys::AltRight : KeyboardKeys::AltLeft);
                    break;

                    //------------------------------------
                    // Special Keys

                case VK_BACK:
                    key = KeyboardKeys::Backspace;
                    break;

                case VK_TAB:
                    key = KeyboardKeys::Tab;
                    break;

                case VK_ESCAPE:
                    key = KeyboardKeys::Escape;
                    break;

                case VK_SPACE:
                    key = KeyboardKeys::Space;
                    break;

                case VK_CAPITAL:
                    key = KeyboardKeys::CapsLock;
                    break;

                case VK_PAUSE:
                    key = KeyboardKeys::Pause;
                    break;
                case VK_EXECUTE:
                    key = KeyboardKeys::Execute;
                    break;

                case VK_SNAPSHOT:
                    key = KeyboardKeys::PrintScreen;
                    break;

                case VK_OEM_PLUS:
                    key = KeyboardKeys::Plus;
                    break;

                case VK_OEM_MINUS:
                    key = KeyboardKeys::Subtract;
                    break;

                case VK_OEM_1:
                    key = KeyboardKeys::Semicolon;
                    break;

                case VK_OEM_2:
                    key = KeyboardKeys::ForwardSlash;
                    break;

                case VK_OEM_3:
                    key = KeyboardKeys::Apostrophe;
                    break;

                case VK_OEM_4:
                    key = KeyboardKeys::BracketLeft;
                    break;

                case VK_OEM_5:
                    key = KeyboardKeys::Backslash;
                    break;

                case VK_OEM_6:
                    key = KeyboardKeys::BracketRight;
                    break;

                case VK_OEM_7:
                    key = KeyboardKeys::QuotationSingle;
                    break;

                case VK_OEM_PERIOD:
                    key = KeyboardKeys::Period;
                    break;

                case VK_OEM_COMMA:
                    key = KeyboardKeys::Comma;
                    break;

                case VK_LWIN:
                case VK_RWIN:
                    key = KeyboardKeys::OSKey;
                    break;

                    //------------------------------------
                    // Numpad Keys

                case VK_DIVIDE:
                    key = KeyboardKeys::NumpadDivide;
                    break;

                case VK_MULTIPLY:
                    key = KeyboardKeys::NumpadMultiply;
                    break;

                case VK_SUBTRACT:
                    key = KeyboardKeys::NumpadSubtract;
                    break;

                case VK_DECIMAL:
                    key = KeyboardKeys::NumpadDecimal;
                    break;

                case VK_RETURN:
                    key = (isE0 ? KeyboardKeys::NumpadEnter : KeyboardKeys::MainpadEnter);
                    break;

                case VK_INSERT:
                    key = (isE0 ? KeyboardKeys::Insert : KeyboardKeys::Numpad0);
                    break;

                case VK_DELETE:
                    key = (isE0 ? KeyboardKeys::Delete : KeyboardKeys::NumpadDecimal);
                    break;

                case VK_HOME:
                    key = (isE0 ? KeyboardKeys::Home : KeyboardKeys::Numpad7);
                    break;

                case VK_END:
                    key = (isE0 ? KeyboardKeys::End : KeyboardKeys::Numpad1);
                    break;

                case VK_PRIOR:
                    key = (isE0 ? KeyboardKeys::PageUp : KeyboardKeys::Numpad9);
                    break;

                case VK_NEXT:
                    key = (isE0 ? KeyboardKeys::PageDown : KeyboardKeys::Numpad3);
                    break;

                case VK_LEFT:
                    key = (isE0 ? KeyboardKeys::LeftArrow : KeyboardKeys::Numpad4);
                    break;

                case VK_RIGHT:
                    key = (isE0 ? KeyboardKeys::RightArrow : KeyboardKeys::Numpad6);
                    break;

                case VK_UP:
                    key = (isE0 ? KeyboardKeys::UpArrow : KeyboardKeys::Numpad8);
                    break;

                case VK_DOWN:
                    key = (isE0 ? KeyboardKeys::DownArrow : KeyboardKeys::Numpad2);
                    break;

                case VK_CLEAR:
                    key = (isE0 ? KeyboardKeys::Clear : KeyboardKeys::Numpad5);
                    break;

                default:

                    if(virtualKey >= 0x30 && virtualKey <= 0x39)
                    {
                        // Mainpad 0-9
                        key = static_cast<KeyboardKeys>(static_cast<uint32_t>(KeyboardKeys::Mainpad0) + (virtualKey - 0x30));
                    }
                    else if((virtualKey >= 0x41) && (virtualKey <= 0x5A))
                    {
                        // A-Z 
                        key = static_cast<KeyboardKeys>(static_cast<uint32_t>(KeyboardKeys::A) + (virtualKey - 0x41));
                    }
                    else if((virtualKey >= 0x70) && (virtualKey <= 0x87))
                    {
                        // F1-F24
                        key = static_cast<KeyboardKeys>(static_cast<uint32_t>(KeyboardKeys::F1) + (virtualKey - 0x70));
                    }
                }

                //--------------------------------------------------------
                // Alert the input handler

                if(key != KeyboardKeys::Undefined)
                {
                    const bool wasUp = ((flags & RI_KEY_BREAK) != 0);

                    if(!wasUp)
                    {
                        // Is now pressed down
                        OcularInput->triggerKeyboardKeyDown(key);
                    }
                    else
                    {
                        // Is now released up
                        OcularInput->triggerKeyboardKeyUp(key);
                    }
                }
            }
        }

        void WindowWin32::handleRawMouseInput(RAWMOUSE const& data)
        {
            if(data.usButtonFlags)
            {
                handleRawMouseButtonInput(data);
            }

            handleRawMouseMoveInput(data);
        }

        void WindowWin32::handleRawMouseButtonInput(RAWMOUSE const& data)
        {
            /**
             * Multiple buttons can (rarely) be pressed/released at the exact same time,
             * which we do not want to risk missing. Must check the following bits:
             *
             *     0000 0000 0001: Left Mouse Down
             *     0000 0000 0010: Left Mouse Up
             *     0000 0000 0100: Right Mouse Down
             *     0000 0000 1000: Right Mouse Up
             *     0000 0001 0000: Middle Mouse Down
             *     0000 0010 0000: Middle Mouse Up
             *     0000 0100 0000: XButton1 Down
             *     0000 1000 0000: XButton1 Up
             *     0001 0000 0000: XButton2 Down
             *     0010 0000 0000: XButton2 Up
             *     0100 0000 0000: Mouse Wheel Changed
             */

            const std::bitset<16> bits(data.usButtonFlags);

            //--------------------------------------------------------
            // Check for left button press/release

            if(bits[0])
            {
                OcularInput->triggerMouseButtonDown(MouseButtons::Left);
            }
            else if(bits[1])
            {
                OcularInput->triggerMouseButtonUp(MouseButtons::Left);
            }

            //--------------------------------------------------------
            // Check for right button press/release

            if(bits[2])
            {
                OcularInput->triggerMouseButtonDown(MouseButtons::Right);
            }
            else if(bits[3])
            {
                OcularInput->triggerMouseButtonUp(MouseButtons::Right);
            }

            //--------------------------------------------------------
            // Check for middle button press/release

            if(bits[4])
            {
                OcularInput->triggerMouseButtonDown(MouseButtons::Middle);
            }
            else if(bits[5])
            {
                OcularInput->triggerMouseButtonUp(MouseButtons::Middle);
            }

            //--------------------------------------------------------
            // Check for XButton1 press/release

            if(bits[6])
            {
                OcularInput->triggerMouseButtonDown(MouseButtons::XButton1);
            }
            else if(bits[7])
            {
                OcularInput->triggerMouseButtonUp(MouseButtons::XButton1);
            }

            //--------------------------------------------------------
            // Check for XButton2 press/release

            if(bits[8])
            {
                OcularInput->triggerMouseButtonDown(MouseButtons::XButton2);
            }
            else if(bits[9])
            {
                OcularInput->triggerMouseButtonUp(MouseButtons::XButton2);
            }

            //--------------------------------------------------------
            // Handle mouse wheel change

            if(bits[10])
            {
                OcularInput->triggerMouseScrollDelta(static_cast<int8_t>(data.usButtonData));
            }
        }

        void WindowWin32::handleRawMouseMoveInput(RAWMOUSE const& data)
        {
            if(data.lLastX != 0 || data.lLastY != 0)
            {
                OcularInput->triggerMouseMoveDelta(Math::Vector2i(data.lLastX, data.lLastY));
            }
        }
    }
}