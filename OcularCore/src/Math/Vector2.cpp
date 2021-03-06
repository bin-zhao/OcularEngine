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

#include "Math/Vector2.hpp"
#include "Utilities/StringRegistrar.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        OCULAR_REGISTER_TO_STRING(Vector2f, OCULAR_TO_STRING_LAMBDA 
        { 
            std::string result;

            if(raw)
            {
                if(!isPointer)
                {
                    Vector2f vector = void_cast<Vector2f>(raw);

                    std::stringstream sstream;
                    sstream << vector.x << " " << vector.y;

                    result = sstream.str();
                }
                else
                {
                    Vector2f* vector = void_cast<Vector2f*>(raw);

                    if(vector)
                    {
                        std::stringstream sstream;
                        sstream << vector->x << " " << vector->y;

                        result = sstream.str();
                    }
                }
            }

            return result; 
        });

        OCULAR_REGISTER_FROM_STRING(Vector2f, OCULAR_FROM_STRING_LAMBDA
        {
            if(out)
            {
                Vector2f* result = void_cast<Vector2f*>(out);

                if(result)
                {
                    size_t cumulativePos = 0;
                    size_t nextPos = 0;

                    try
                    {
                        result->x = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->y = std::stof(str.substr(cumulativePos), &nextPos);
                    }
                    catch(std::invalid_argument const& e)
                    {
                        OcularLogger->error("Failed to convert string '", str, "' to Vector2f with error: ", e.what(), OCULAR_INTERNAL_LOG("Vector2f", "FromString"));
                    }
                }
            }
        });

        bool Vector2f::OCULAR_INTERNAL_Force = false;

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

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