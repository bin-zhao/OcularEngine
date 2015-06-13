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

#include "Math/Geometry/Frustum.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Bounds/BoundsSphere.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Frustum::Frustum(Matrix4x4f const& viewProjection)
        {
            setViewProjection(viewProjection);
        }

        Frustum::Frustum()
        {
        
        }

        Frustum::~Frustum()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Frustum::setViewProjection(Matrix4x4f const& viewProjection)
        {
            // Source: http://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
            // http://zach.in.tu-clausthal.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
        }

        bool Frustum::contains(BoundsSphere const& bounds, IntersectionType* result) const
        {
            return false;
        }

        bool Frustum::contains(BoundsAABB const& bounds, IntersectionType* result) const
        {
            return false;
        }

        bool Frustum::contains(BoundsOBB const& bounds, IntersectionType* result) const
        {
            return false;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}