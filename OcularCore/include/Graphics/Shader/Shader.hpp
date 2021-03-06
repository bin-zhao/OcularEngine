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
#ifndef __H__OCULAR_GRAPHICS_SHADER__H__
#define __H__OCULAR_GRAPHICS_SHADER__H__

#include "Resources/Resource.hpp"

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
        class ShaderProgram;

        /**
         * \class Shader
         */
        class Shader : public Core::Resource
        {
            friend class ShaderProgram;

        public:

            Shader();
            virtual ~Shader();

            virtual void unload() = 0;

            /**
             * Binds the shader and sets it as the active render shader.
             */
            virtual void bind() = 0;

            /**
             * Unbinds the shader as the active render shader.
             */
            virtual void unbind() = 0;

            /**
             * \return The ShaderProgram that owns this Shader
             */
            ShaderProgram* getParent() const;

        protected:

            ShaderProgram* m_Parent;

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