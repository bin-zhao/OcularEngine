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
#ifndef __H__OCULAR_D3D11_GRAPHICS_VERTEX_SHADER__H__
#define __H__OCULAR_D3D11_GRAPHICS_VERTEX_SHADER__H__

#include "Graphics/Shader/VertexShader.hpp"
#include <d3d11.h>

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
         * \class D3D11VertexShader 
         */
        class D3D11VertexShader : public VertexShader 
        {
        public:

            D3D11VertexShader(ID3D11Device* device);
            ~D3D11VertexShader();

            virtual void unload() override;
            virtual void bind() override;
            virtual void unbind() override;

            /**
             * Sets the D3D-specific shader owned by this object.
             *
             * Note that this object will take full ownership of the shader instance and release it upon it's own unload/destruction.
             * If this object already owns a D3D shader, it will release it prior to assuming ownership.
             *
             * \param[in] shader New ID3D11VertexShader instance
             */
            void setD3DShader(ID3D11VertexShader* shader);

            /**
             * \return The current D3D11-specific shader interface. May return NULL if none present.
             */
            ID3D11VertexShader* getD3DShader();

            /**
             * Sets the ID3DBlob of information associated with this shader.
             *
             * Note that this object will take full ownership of the blob and release it upon it's own unload/destruction.
             * If this object already owns a D3D blob, it will release it prior to assuming ownership.
             *
             * \param[in] blob New ID3DBlob instance
             */
            void setD3DBlob(ID3DBlob* blob);
            
            /**
             * \return The ID3DBlob of information associated with this shader. May return NULL if none present.
             */
            ID3DBlob* getD3DBlob();

        protected:
            
            ID3D11Device* m_D3DDevice;
            ID3D11VertexShader* m_D3DShader;
            ID3DBlob* m_D3DBlob;

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