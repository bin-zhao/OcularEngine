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
#ifndef __H__OCULAR_GRAPHICS_GRAPHICS_MATERIAL_H__
#define __H__OCULAR_GRAPHICS_GRAPHICS_MATERIAL_H__

#include "Graphics/Shader/Uniform/UniformBuffer.hpp"
#include "Graphics/RenderState/RasterState.hpp"
#include "Renderer/RenderPriority.hpp"

#include "Resources/Resource.hpp"
#include "ObjectIO/ObjectIO.hpp"
#include "Math/Matrix4x4.hpp"
#include "Math/Color.hpp"

#include <unordered_map>

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
        class Texture;
        class VertexShader;
        class GeometryShader;
        class FragmentShader;
        class PreTessellationShader;
        class PostTessellationShader;

        struct TextureSamplerInfo
        {
            Texture* texture;
            std::string samplerName;
            uint32_t samplerRegister;
        };

        /**
         * \class Material
         */
        class Material : public Core::Resource, public Core::ObjectIO
        {
        public:

            Material();
            virtual ~Material();

            virtual void bind();
            virtual void unbind();

            virtual void unload() override;

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            virtual void onLoad(Core::BuilderNode const* node) override;
            virtual void onSave(Core::BuilderNode* node) const override;

            //------------------------------------------------------------
            // Texture Methods
            //------------------------------------------------------------

            /**
             * Assigns a texture to a specific input register for use by the shaders
             * that are part of this material. All textures are automatically bound
             * to all relevant (non-NULL) shader stages.
             *
             * Depending on the underlying graphics API, and shader implementation language,
             * some may make use of the index or the name or both. 
             *
             * Note that some texture assignment indices and names are reserved by the engine.
             * See ------- for a list of all reserved locations.
             *
             * \param[in] index   The index to bind the texture to. This can be on the range of
             *                    0 to (GraphicsDriver::getMaxBoundTextures - 1). Note that indices
             *                    do not have to be sequential. For example, you may have use 0, 1, 3, 79.
             * \param[in] name    The name to bind the texture to.
             * \param[in] texture The texture to bind.
             *
             * \return TRUE if texture was successfully set. May fail due to invalid index value.
             */
            virtual bool setTexture(uint32_t index, std::string const& name, Texture* texture);

            /**
             * Retrieves the texture stored at the specified identifier.
             * \param[in] index Index of the texture to retrieve.
             */
            Texture* getTexture(uint32_t index) const;

            /**
             * Removes the texture at the specified index from this material.
             * \param[in] index
             */
            virtual void removeTexture(uint32_t index);

            /**
             * \return Number of textures attached to this material.
             */
            uint32_t getNumTextures() const;

            /**
             * \return Vector of all textures attached to this material.
             * \note Returned vector is read-only. See Material::setTexture and Material::removeTexture to modify.
             */
            std::vector<TextureSamplerInfo> const* getTextures() const;

            //------------------------------------------------------------
            // Shader Methods
            //------------------------------------------------------------

            /**
             * Sets the vertex shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a vertex shader.
             */
            bool setVertexShader(std::string const& name);

            /**
             * Sets the vertex shader used by this Material.
             * \param[in] shader Pointer to the shared vertex shader to use.
             */
            void setVertexShader(VertexShader* shader);

            /**
             * Sets the geometry shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a geometry shader.
             */
            bool setGeometryShader(std::string const& name);

            /**
             * Sets the geometry shader used by this Material.
             * \param[in] shader Pointer to the shared geometry shader to use.
             */
            void setGeometryShader(GeometryShader* shader);

            /**
             * Sets the fragment shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a fragment shader.
             */
            bool setFragmentShader(std::string const& name);

            /**
             * Sets the fragment shader used by this Material.
             * \param[in] shader Pointer to the shared fragment shader to use.
             */
            void setFragmentShader(FragmentShader* shader);

            /**
             * Sets the pre-tessellation shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a pre-tessellation shader.
             */
            bool setPreTessellationShader(std::string const& name);

            /**
             * Sets the pre-tessellation shader used by this Material.
             * \param[in] shader Pointer to the shared pre-tessellation shader to use.
             */
            void setPreTessellationShader(PreTessellationShader* shader);

            /**
             * Sets the post-tessellation shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a post-tessellation shader.
             */
            bool setPostTessellationShader(std::string const& name);

            /**
             * Sets the post-tessellation shader used by this Material.
             * \param[in] shader Pointer to the shared post-tessellation shader to use.
             */
            void setPostTessellationShader(PostTessellationShader* shader);

            /**
             * \return The vertex shader used by this material. May be NULL if no valid shader is set.
             */
            VertexShader* getVertexShader() const;

            /**
             * \return The geometry shader used by this material. May be NULL if no valid shader is set.
             */
            GeometryShader* getGeometryShader() const;

            /**
             * \return The fragment shader used by this material. May be NULL if no valid shader is set.
             */
            FragmentShader* getFragmentShader() const;

            /**
             * \return The pre-tessellation shader used by this material. May be NULL if no valid shader is set.
             */
            PreTessellationShader* getPreTessellationShader() const;

            /**
             * \return The post-tessellation shader used by this material. May be NULL if no valid shader is set.
             */
            PostTessellationShader* getPostTessellationShader() const;

            //------------------------------------------------------------
            // Uniform Methods
            //------------------------------------------------------------

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             *
             * \param[in] name          Valid uniform name.
             * \param[in] registerIndex First register that the uniform occupies. Each register is 16 bytes, and a single uniform may occupy multiple registers at once.
             * \param[in] value         Single floating-point value for the uniform.
             *
             * \return TRUE if the Uniform value was set successfully. May fail due to invalid index, etc.
             */
            virtual void setUniform(std::string const& name, uint32_t registerIndex, float value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, float& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             *
             * \param[in] name          Valid uniform name.
             * \param[in] registerIndex First register that the uniform occupies. Each register is 16 bytes, and a single uniform may occupy multiple registers at once.
             * \param[in] value         A 4-component Vector value for the uniform.
             *
             * \return TRUE if the Uniform value was set successfully. May fail due to invalid index, etc.
             */
            virtual void setUniform(std::string const& name, uint32_t registerIndex, Math::Vector4f const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Vector4f& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             *
             * \param[in] name          Valid uniform name.
             * \param[in] registerIndex First register that the uniform occupies. Each register is 16 bytes, and a single uniform may occupy multiple registers at once.
             * \param[in] value         An RGBA color value for the uniform.
             *
             * \return TRUE if the Uniform value was set successfully. May fail due to invalid index, etc.
             */
            virtual void setUniform(std::string const& name, uint32_t registerIndex, Core::Color const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Core::Color& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             *
             * \param[in] name          Valid uniform name.
             * \param[in] registerIndex First register that the uniform occupies. Each register is 16 bytes, and a single uniform may occupy multiple registers at once.
             * \param[in] value         A 3x3 matrix value for the uniform.
             *
             * \return TRUE if the Uniform value was set successfully. May fail due to invalid index, etc.
             */
            virtual void setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix3x3 const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Matrix3x3& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             *
             * \param[in] name          Valid uniform name.
             * \param[in] registerIndex First register that the uniform occupies. Each register is 16 bytes, and a single uniform may occupy multiple registers at once.
             * \param[in] value         A 4x4 matrix value for the uniform.
             *
             * \return TRUE if the Uniform value was set successfully. May fail due to invalid index, etc.
             */
            virtual void setUniform(std::string const& name, uint32_t registerIndex, Math::Matrix4x4 const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Matrix4x4& value);

            /**
             * \return Constant pointer to the UniformBuffer
             */
            UniformBuffer const* getUniformBuffer() const;

            //------------------------------------------------------------
            // Render State Changes
            //------------------------------------------------------------

            /**
             * Sets the primitive style that the material should render as.
             * \param[in] style
             */
            void setPrimitiveStyle(PrimitiveStyle style);

            /**
             * \return Primitive style used by this material
             */
            PrimitiveStyle getPrimitiveStyle() const;

            /**
             * Sets the fill mode that the material should render as.
             * \param[in] fill
             */
            void setFillMode(FillMode mode);

            /**
             * \return Fill mode used by this material
             */
            FillMode getFillMode() const;

            /**
             * Sets the priority of the material in the render queue.
             * 
             * See Graphics::RenderPriority for pre-set priority values.
             *
             * \param[in] priority
             */
            void setRenderPriority(uint32_t priority);

            /**
             * \return The render priority assigned to this Material
             */
            uint32_t getRenderPriority() const;

            //------------------------------------------------------------
            // Node Names (used for saving and loading)

            static const std::string ShaderNodeName;
            static const std::string TexturesNodeName;
            static const std::string TextureNodeName;
            static const std::string UniformsNodeName;
            static const std::string UniformNodeName;
            static const std::string RenderStateNodeName;

        protected:

            void setDefaults();

            void bindShaders();
            void unbindShaders();

            void bindStateChanges();
            void unbindStateChanges();

            void onLoadShaders(Core::BuilderNode const* parent);
            void onLoadTextures(Core::BuilderNode const* parent);
            void onLoadUniforms(Core::BuilderNode const* parent);
            void onLoadUniform(Core::BuilderNode const* parent, Uniform* uniform);
            void onLoadRenderState(Core::BuilderNode const* parent);

            void onSaveShaders(Core::BuilderNode* parent) const;
            void onSaveTextures(Core::BuilderNode* parent) const;
            void onSaveUniforms(Core::BuilderNode* parent) const;
            void onSaveUniform(Core::BuilderNode* parent, Uniform const* uniform) const;
            void onSaveRenderState(Core::BuilderNode* parent) const;

            //------------------------------------------------------------

            VertexShader*           m_VertexShader;
            GeometryShader*         m_GeometryShader;
            FragmentShader*         m_FragmentShader;
            PreTessellationShader*  m_PreTessellationShader;
            PostTessellationShader* m_PostTessellationShader;

            RasterState m_StoredRasterState;

            std::vector<TextureSamplerInfo> m_Textures;
            UniformBuffer* m_UniformBuffer;

            uint32_t m_RenderPriority;

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