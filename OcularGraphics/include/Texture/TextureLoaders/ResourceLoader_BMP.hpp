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
#ifndef __H__OCULAR_GRAPHICS_RESOURCE_LOADER_BMP__H__
#define __H__OCULAR_GRAPHICS_RESOURCE_LOADER_BMP__H__

#include "Resources/ResourceLoader.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class ResourceLoader_BMP
         *
         * Implementation of AResourceLoader that handles the loading of
         * files with the '.bmp' extension.
         *
         * These files are loaded as a Texture2D.
         */
        class ResourceLoader_BMP : public Core::AResourceLoader
        {
        public:

            ResourceLoader_BMP();
            virtual ~ResourceLoader_BMP();

            virtual bool loadResource(Core::Resource* resource, Core::File const& file);

        protected:

            bool isValidFile(Core::File const& file);
            
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