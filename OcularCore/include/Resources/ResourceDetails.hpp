/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_DETAILS__H__
#define __H__OCULAR_RESOURCES_RESOURCE_DETAILS__H__

#include "Resource.hpp"
#include <memory>

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
         * \class ResourceDetails
         * \brief Maintains a resource and usage details.
         */
        class ResourceDetails
        {
        public:

            ResourceDetails(std::shared_ptr<Resource> resource);
            ~ResourceDetails();

            /**
             *
             */
            std::shared_ptr<Resource> getResource();

            /**
             *
             */
            std::shared_ptr<Resource> getResourceUntracked() const;

            /**
             *
             */
            unsigned long long getTimeOfLastRequest() const;

            /**
             *
             */
            unsigned getNumberOfRequests() const;

            /**
             *
             */
            unsigned long long getSize() const;

            /**
             *
             */
            void reset();
        
        protected:
        
        private:

            std::shared_ptr<Resource> m_Resource;

            unsigned long long m_LastRequest;  /// In NS
            unsigned m_NumberOfRequests;
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