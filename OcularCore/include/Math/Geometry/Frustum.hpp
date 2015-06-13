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
#ifndef __H__OCULAR_MATH_FRUSTUM__H__
#define __H__OCULAR_MATH_FRUSTUM__H__

#include "Math/Matrix4x4.hpp"
#include "Math/Geometry/Plane.hpp"
#include <array>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        class BoundsAABB;
        class BoundsOBB;
        class BoundsSphere;

        /**
         * \class Frustum
         */
        class Frustum
        {
        public:

            Frustum(Matrix4x4f const& viewProjection);
            Frustum();

            ~Frustum();

            /**
             * Sets the view-projection matrix that this frustum is based off of.
             * \param[in] viewProjection
             */
            void setViewProjection(Matrix4x4f const& viewProjection);

            /**
             * Tests to determine if the frustum contains the specified bounding sphere.
             *
             * \param[in] point
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(Point3f const& point) const;

            /**
             * Tests to determine if the frustum contains the specified bounding sphere.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsSphere const& bounds) const;
            
            /**
             * Tests to determine if the frustum contains the specified AABB.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsAABB const& bounds) const;
            
            /**
             * Tests to determine if the frustum contains the specified OBB.
             *
             * \param[in] bounds
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsOBB const& bounds) const;

        protected:

        private:

            Plane m_Left;
            Plane m_Right;
            Plane m_Top;
            Plane m_Bottom;
            Plane m_Near;
            Plane m_Far;
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