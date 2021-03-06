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

#include "Math/Transform.hpp"
#include "Math/Euler.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Vector4.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Transform::Transform(Vector3f const& position, Quaternion const& rotation, Vector3f const& scale)
            : m_Position(position), 
              m_Rotation(rotation), 
              m_Scale(scale),
              m_DirtyFlags(0)
        {
            OCULAR_EXPOSE(m_Position);
            OCULAR_EXPOSE(m_Rotation);
            OCULAR_EXPOSE(m_Scale);
        }

        Transform::Transform()
            : m_Scale(Vector3f(1.0f, 1.0f, 1.0f)),
              m_DirtyFlags(0)
        {
            OCULAR_EXPOSE(m_Position);
            OCULAR_EXPOSE(m_Rotation);
            OCULAR_EXPOSE(m_Scale);
        }

        Transform::~Transform()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void Transform::refresh()
        {
            m_ModelMatrix = Matrix4x4(m_Position, m_Rotation, m_Scale);
        }

        //----------------------------------------------------------------
        // Getters and Setters
        //----------------------------------------------------------------

        uint32_t Transform::getDirtyFlags(bool const clearFlags)
        {
            const uint32_t result = m_DirtyFlags;

            if(clearFlags)
            {
                m_DirtyFlags = 0;
            }

            return result;
        }

        void Transform::setPosition(Vector3f const& position)
        {
            m_Position = position;
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Position);

            refresh();
        }

        void Transform::setPosition(float const x, float const y, float const z)
        {
            m_Position.x = x;
            m_Position.y = y;
            m_Position.z = z;

            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Position);
            
            refresh();
        }

        Vector3f const& Transform::getPosition() const
        {
            return m_Position;
        }

        void Transform::setRotation(Quaternion const& rotation)
        {
            m_Rotation = rotation;
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Rotation);

            refresh();
        }

        Quaternion const& Transform::getRotation() const
        {
            return m_Rotation;
        }

        void Transform::setScale(Vector3f const& scale)
        {
            m_Scale = scale;
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Scale);

            refresh();
        }

        Vector3f const& Transform::getScale() const
        {
            return m_Scale;
        }

        Vector3f Transform::getForwards() const
        {
            Vector3f result;
            Matrix3x3 mat(m_Rotation);

            mat.getCol(2, result);

            return result;
        }

        Vector3f Transform::getUp() const
        {
            Vector3f result;
            Matrix3x3 mat(m_Rotation);

            mat.getCol(1, result);

            return result;
        }

        Vector3f Transform::getRight() const
        {
            Vector3f result;
            Matrix3x3 mat(m_Rotation);

            mat.getCol(0, result);

            return result;
        }

        Matrix4x4 const& Transform::getModelMatrix() const
        {
            return m_ModelMatrix;
        }
        
        //----------------------------------------------------------------
        // Movement
        //----------------------------------------------------------------

        void Transform::translate(Vector3f const& translation, bool local)
        {
            if(local)
            {
                m_Position += (Matrix3x3(m_Rotation) * translation);
            }
            else
            {
                m_Position += translation;
            }
            
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Position);
            refresh();
        }

        void Transform::moveForward(float const delta)
        {
            translate(getForwards() * delta);
        }

        void Transform::moveUp(float const delta)
        {
            translate(getUp() * delta);
        }

        void Transform::moveRight(float const delta)
        {
            translate(getRight() * delta);
        }
        
        //----------------------------------------------------------------
        // Rotation
        //----------------------------------------------------------------

        void Transform::rotate(float const angle, Vector3f const& axis)
        {
            m_Rotation = Quaternion::Rotate(m_Rotation, angle, axis);
            refresh();

            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Rotation);
        }

        void Transform::rotate(Math::Quaternion const& rotation)
        {
            m_Rotation = m_Rotation * rotation;
            refresh();

            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Rotation);
        }

        void Transform::lookAt(Vector3f const& point, Vector3f const& upVector)
        {
            m_Rotation = Quaternion::CreateLookAtRotation(m_Position, point, upVector).getConjugate();
            refresh();
            
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Position);
            m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Rotation);
        }
        
        //----------------------------------------------------------------
        // Inherited Methods
        //----------------------------------------------------------------

        void Transform::onLoad(Core::BuilderNode const* node)
        {
            ObjectIO::onLoad(node);
            refresh();
        }

        void Transform::onVariableModified(std::string const& varName)
        {
            if(Utils::String::IsEqual(varName, "m_Position"))
            {
                m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Position);
            }
            else if(Utils::String::IsEqual(varName, "m_Rotation"))
            {
                m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Rotation);
            }
            else if(Utils::String::IsEqual(varName, "m_Scale"))
            {
                m_DirtyFlags |= static_cast<uint32_t>(DirtyFlags::Scale);
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}