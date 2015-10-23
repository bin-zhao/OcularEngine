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

#include "Graphics/Texture/NoiseTexture2D.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        NoiseTexture2D::NoiseTexture2D(std::shared_ptr<Math::Random::ARandom> prng, uint32_t width, uint32_t height, TextureFilterMode filter, TextureUsageMode usage)
            : Texture2D(width, height, filter, usage)
        {
            uint32_t numPixels = width * height;
            float pixelColor = 0.0f;
            
            m_Pixels.reserve(numPixels);

            for(uint32_t i = 0; i < numPixels; i++)
            {
                if(prng)
                {
                    pixelColor = prng->nextf();
                }

                m_Pixels[i] = Core::Color(pixelColor, pixelColor, pixelColor, 1.0f);
            }

            m_IsInMemory = true;
        }

        NoiseTexture2D::NoiseTexture2D(std::shared_ptr<Math::Noise::ANoise> noise, uint32_t width, uint32_t height, uint32_t xOffset, uint32_t yOffset, TextureFilterMode filter, TextureUsageMode usage)
            : Texture2D(width, height, filter, usage)
        {
            uint32_t numPixels = width * height;
            float pixelColor = 0.0f;
            
            m_Pixels.reserve(numPixels);

            for(uint32_t y = 0; y < height; y++)
            {
                for(uint32_t x = 0; x < width; x++)
                {
                    if(noise)
                    {
                        // Noise methods return on range [-1.0, 1.0] but we want [0.0, 1.0]
                        pixelColor = (noise->getValue(static_cast<float>(x + xOffset), static_cast<float>(y + yOffset)) + 1.0f) * 0.5f;
                    }

                    m_Pixels[(y * width) + x] = Core::Color(pixelColor, pixelColor, pixelColor, 1.0f);
                }
            }

            m_IsInMemory = true;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}