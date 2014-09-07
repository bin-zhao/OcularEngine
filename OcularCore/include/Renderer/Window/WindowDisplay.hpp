/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_RENDERER_WINDOW_DISPLAY__H__
#define __H__OCULAR_RENDERER_WINDOW_DISPLAY__H__

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \enum WINDOW_DISPLAY_MODE
     */
    enum WINDOW_DISPLAY_MODE
    {
        WINDOWED_BORDERED = 0x0,    ///< Window with dimensions equal to resolution with added border
        WINDOWED_NO_BORDER,         ///< Window with dimensions equal to resolution and no border
        FULLSCREEN_BORDERED,        ///< Fullscreen with border
        FULLSCREEN_NO_BORDER        ///< Fullscreen with no border
    };
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif