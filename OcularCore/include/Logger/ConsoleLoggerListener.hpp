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
#ifndef __H__OCULAR_LOGGER_CONSOLE_LISTENER__H__
#define __H__OCULAR_LOGGER_CONSOLE_LISTENER__H__

#include "Logger\ILoggerListener.hpp"

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
         * \class ConsoleLoggerListener
         *
         * Implementation of the ILoggerListener interface that outputs Logger
         * messages to the standard console.
         */
        class ConsoleLoggerListener : public ILoggerListener
        {
        public:
        
            ConsoleLoggerListener();
            ~ConsoleLoggerListener();

            virtual void onLogMessage(LoggerMessage const& message) override;

        protected:

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
* @} End of Doxygen Groups
*/

//------------------------------------------------------------------------------------------

#endif