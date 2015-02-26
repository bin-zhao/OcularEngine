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

#include "Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"
#include "OcularEngine.hpp"

#include <fstream>

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::TextureResourceLoader_BMP)

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceLoader_BMP::TextureResourceLoader_BMP()
            : TextureResourceLoader(".bmp")
        {

        }

        TextureResourceLoader_BMP::~TextureResourceLoader_BMP()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader_BMP::readFile(Core::File const& file, std::vector<Color>& pixels, unsigned& width, unsigned& height)
        {
            bool result = false;
            std::vector<char> buffer;

            loadFileIntoBuffer(file, buffer);

            if(buffer.size() > 0)
            {
                
            }
            else
            {
                OcularLogger->error("File buffer is empty", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readFile"));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}