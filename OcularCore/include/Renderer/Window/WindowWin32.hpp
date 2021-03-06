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

#pragma once
#ifndef __H__OCULAR_RENDERER_WIN_WINDOW__H__
#define __H__OCULAR_RENDERER_WIN_WINDOW__H__

#include "Common.hpp"
#include "Window.hpp"

#ifdef OCULAR_WINDOWS
#include <Windows.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{ 
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class WindowWin32
         *
         * Implementation of the abstract Window class.<br/>
         * Used for the creation of a Win32 Window.
         */
        class WindowWin32 : public AWindow
        {
        public:

            /**
             * \param name
             * \param width
             * \param height
             * \param colorBits
             * \param depthBits
             * \param stencilBits
             * \param display
             * \param alwaysOnTop
             */
            WindowWin32(WindowDescriptor const& descriptor);

            /**
             *
             */
            WindowWin32(WindowDescriptor const& descriptor, void* windowID);

            virtual ~WindowWin32();

            /**
             * Turns the cursor on and off.
             * \param[in] show If TRUE, the cursor is displayed.
             */
            virtual void showCursor(bool show) override;

            /**
             * Returns the HWND owned by this Window instance.
             * \return HWND
             */
            HWND getHWND() const;

            /**
             * Returns the HINSTANCE owned by this Window instance.
             * \return HINSTANCE
             */
            HINSTANCE getHINSTANCE() const;

            /**
             * Class implementation of WndProc.<br/>
             * Passes Windows messages to the Ocular message handler.<br/><br/>
             *
             * See: http://web.archive.org/web/20051125022758/www.rpi.edu/~pudeyo/articles/wndproc/
             *
             * \param hWnd
             * \param uMsg
             * \param wParam
             * \param lParam
             */
            LRESULT CALLBACK processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        protected:

            /**
             * See ::Window::open
             */
            void open();

            /**
             *
             */
            void connect();

            /**
             * See ::Window::update
             */
            void update(uint64_t time);

            /**
             * See ::Window::close
             */
            void close();

        private:

            /**
             * \return RECT instance
             */
            RECT createWindowRect();

            /**
             * \param wndProc
             * \return WNDCLASS instance
             */
            WNDCLASS createWndClass(WNDPROC wndProc);

            /**
             * Registers to listen for raw input messages.
             */
            void registerRawInput();

            /**
             *
             */
            void handleRawKeyboardInput(RAWKEYBOARD const& data);

            /**
             * 
             */
            void handleRawMouseInput(RAWMOUSE const& data);

            /**
             * 
             */
            void handleRawMouseButtonInput(RAWMOUSE const& data);

            /**
             * 
             */
            void handleRawMouseMoveInput(RAWMOUSE const& data);

            //------------------------------------------------------------

            HWND      m_HWND;
            HINSTANCE m_HINSTANCE;

            RAWINPUTDEVICE m_RawDevices[2];      ///< The raw input devices. Currently support just two: mouse and keyboard.
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/** 
 * }@ End of Doxygen Groups 
 */

//------------------------------------------------------------------------------------------

#endif // OCULAR_WINDOWS
#endif // __H__OCULAR_RENDERER_WIN_WINDOW__H__