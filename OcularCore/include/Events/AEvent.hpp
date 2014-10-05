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
#ifndef __H__OCULAR_EVENTS_EVENT__H__
#define __H__OCULAR_EVENTS_EVENT__H__

#include <string>
#include "EventPriority.hpp"

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
         * \class EventManager
         */
        class AEvent
        {
        public:

            AEvent(std::string name, EVENT_PRIORITY priority = EVENT_PRIORITY::MEDIUM);
            ~AEvent();

            /**
             *
             */
            std::string getName() const;
            

            /**
             *
             */
            EVENT_PRIORITY getPriority() const;

            /**
             *
             */
            int getUID() const;
            
            /**
             *
             */
            long long getCreationTime() const;

        protected:

        private:

            std::string m_Name;
            EVENT_PRIORITY m_Priority;
            int m_UID;
            long long m_CreationTime;
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